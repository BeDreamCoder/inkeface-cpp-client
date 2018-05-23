#include "SignTx.h"
#include <libdevcore/SHA3.h>
#include <libdevcrypto/Hash.h>
#include <libdevcrypto/CryptoPP.h>
#include "chaincode.pb.h"

using namespace std;
using namespace dev;
using namespace protos;

SignTx::SignTx() {}

SignTx::~SignTx() {}

string SignTx::GetSign(SignParams const& params) const
{
	// auto sec = Secret{sha3("sec")};
	// auto msg = sha3("msg");
	// auto sig = sign(sec, msg);
	// auto expectedSig = "b826808a8c41e00b7c5d71f211f005a84a7b97949d5e765831e1da4e34c9b8295d2a622eee50f25af78241c1cb7cfff11bcf2a13fe65dee1e3b86fd79a4e3ed000";
	// auto pub = recover(sig, msg);
	// auto expectedPub = "e40930c838d6cca526795596e368d16083f0672f4ab61788277abfa23c3740e1cc84453b0b24f49086feba0bd978bb4446bae8dff1e79fcc1e9cf482ec2d07c3";

	auto sec = Secret{fromHex(params.prikey)};
 	auto sender = 'i' + toAddress(sec).hex();

	SignContent signContent;
	ChaincodeSpec *ccSpec = signContent.mutable_chaincode_spec();
	ccSpec->set_type(ChaincodeSpec_Type_GOLANG);

	ChaincodeID * pCcId = ccSpec->mutable_chaincode_id();
	pCcId->set_name(params.ccId);

	ChaincodeInput *pInput = ccSpec->mutable_input();
	pInput->add_args(params.fcn.empty() ? "invoke" : params.fcn);
	for(args_vec::const_iterator it = params.args.begin(); it != params.args.end(); it++) {
		pInput->add_args(*it);
	}

	ChaincodeInvocationSpec cis;
	signContent.set_id_generation_alg(cis.id_generation_alg());

	SenderSpec *pSenderSpec = signContent.mutable_sender_spec();
	pSenderSpec->set_sender(sender);
	pSenderSpec->set_counter(params.counter);
	pSenderSpec->set_ink_limit(params.inkLimit);
	pSenderSpec->set_msg(params.msg);

	string sData;
	signContent.SerializeToString(&sData);
	auto msg = sha256(bytesConstRef(sData));
	auto sig = sign(sec, msg);
	return sig.hex();
}

Account SignTx::CreateAccount() const
{
	auto keyPair = KeyPair::create();
	Account account = {'i' + keyPair.address().hex(), keyPair.pub().hex(), keyPair.secret().makeInsecure().hex()};
	// std::cout << keyPair.pub() << std::endl;
	// std::cout << keyPair.secret().makeInsecure().hex() << std::endl;
	// std::cout << keyPair.address() << std::endl;
	return account;
}

std::string SignTx::PublicKeyFromPrivate(std::string const& prikey) const {
	auto sec = Secret{fromHex(prikey)};
	auto pub = toPublic(sec);
	return pub.hex();
}
