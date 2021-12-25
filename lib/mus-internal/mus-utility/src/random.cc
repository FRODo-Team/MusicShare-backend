#include "mus-utility/random.h"
#include <random>

namespace music_share::utility {

std::string Random::GenerateString(size_t length) {
    static const std::string characters = std::string{ kCharacters };
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string result;
    for (std::size_t i = 0; i < length; ++i) {
        result += characters[distribution(generator)];
    }

    return result;
}

} // namespace music_share::utility
