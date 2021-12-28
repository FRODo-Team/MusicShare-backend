#include "mus-utility/crypto.h"

#include <iomanip>
#include <sstream>

#include <openssl/sha.h>


namespace music_share::utility {

std::string Crypto::HashString_SHA256(const std::string& s) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, s.c_str(), s.size());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}

std::string Crypto::HashAndSalt(const std::string& s) {
    std::string salted = s + std::string{ kSalt };
    return HashString_SHA256(salted);
}

} // namespace music_share::utility
