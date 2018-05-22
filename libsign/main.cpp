#include "SignTx.h"

int main()
{
    SignTx* st = new SignTx;
    Account a = st->CreateAccount();
    std::cout << "address: " + a.address << std::endl;
	std::cout << "pubkey: " + a.pubkey << std::endl;
	std::cout << "prikey: " + a.prikey << std::endl;
    std::string pubkey = st->PublicKeyFromPrivate(a.prikey);
	std::cout << "PublicKeyFromPrivate: " + pubkey << std::endl;
    
    SignParams param;
    param.ccId = "token";
    param.fcn = "transfer";
    std::vector<std::string> args;
    args.push_back("ie18d6a17742e35eee33324b859fdbfecd85c8f89");
    args.push_back("INK");
    args.push_back("100");
    param.args = args;
    param.counter = 179566;
    param.inkLimit = "100000000000";
    param.msg = "test";
    param.prikey = "99f47fc849b1bdaab2bc6ff369bbb6d94be842a45a4e7322d38cf59de2e6a561";

    std::string sig = st->GetSign(param);
    std::cout << "sig: " + sig << std::endl;
    return 0;
}
