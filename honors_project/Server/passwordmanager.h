#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H
#include "cryptopp/cryptlib.h"
#include "cryptopp/sha.h"
#include "cryptopp/hex.h"

class PasswordManager{
public:
    std::string hashPassword(std::string data);
};

#endif // PASSWORDMANAGER_H
