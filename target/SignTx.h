#pragma once

#include <iostream>
#include <vector>

struct Account
{
    std::string address;
    std::string pubkey;
    std::string prikey;
};

typedef std::vector<std::string> args_vec;

struct SignParams
{
    std::string ccId;
    std::string fcn;
    args_vec    args;
    long 		counter;
    std::string inkLimit;
    std::string msg;
    std::string prikey;
};

class SignTx
{
public:
	SignTx();
	~SignTx();

	std::string GetSign(SignParams const& params) const;

	Account CreateAccount() const;

	std::string PublicKeyFromPrivate(std::string const& prikey) const;
};


