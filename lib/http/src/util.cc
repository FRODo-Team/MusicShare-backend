#include "util.h"

namespace music_share {
namespace http {
namespace util {

std::vector<std::string> split(const std::string& seq,
                               const std::string& sep) {
    std::vector<std::string> tokens;

    size_t lo = 0;
    size_t hi = 0;
    while ((hi = seq.find(sep, lo)) != std::string::npos) {
        tokens.push_back(seq.substr(lo, hi - lo));
        lo = hi + 1;
    }
    tokens.push_back(seq.substr(lo, hi - lo));

    return tokens;
}

}  // namespace util
}  // namespace http
}  // namespace music_share
