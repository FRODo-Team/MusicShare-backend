#ifndef MUS_INTERNAL_MUS_UTILITY_RANDOM_H_
#define MUS_INTERNAL_MUS_UTILITY_RANDOM_H_

#include <string>

namespace music_share::utility {

class Random final {
public:
    Random() = delete;

    static std::string GenerateString(size_t length);

private:
    static constexpr std::string_view kCharacters = "0123456789"
                                                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                                    "abcdefghijklmnopqrstuvwxyz";
};

} // namespace music_share::utility

#endif // MUS_INTERNAL_MUS_UTILITY_RANDOM_H_
