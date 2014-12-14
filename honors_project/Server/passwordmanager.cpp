#include "passwordmanager.h"

std::string PasswordManager::hashPassword(std::string password){
    byte const* pass = (byte*) password.data();
    unsigned int nDataLen = password.size();
    byte digest[CryptoPP::SHA256::DIGESTSIZE];

    CryptoPP::SHA256().CalculateDigest(digest, pass, nDataLen);

    CryptoPP::HexEncoder encoder;
    std::string output;
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    CryptoPP::word64 size = encoder.MaxRetrievable();
    if(size){
        output.resize(size);
        encoder.Get((byte*)output.data(), output.size());
    }
    return output;
}
