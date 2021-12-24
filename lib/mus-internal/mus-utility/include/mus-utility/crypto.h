#ifndef MUS_INTERNAL_MUS_UTILITY_CRYPTO_H_
#define MUS_INTERNAL_MUS_UTILITY_CRYPTO_H_

#include <string>

namespace music_share::utility {

class Crypto {
public:
    Crypto() = delete;

    static std::string HashString_SHA256(const std::string& s);
};

} // namespace music_share::utility

#endif // MUS_INTERNAL_MUS_UTILITY_CRYPTO_H_
