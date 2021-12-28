// Oweners: Faris Nabiev, WEB-12
#ifndef MUS_HTTP_UTIL_H_
#define MUS_HTTP_UTIL_H_

#include <vector>  // std::vector
#include <string>  // std::string

namespace music_share {
namespace http {
namespace util {

std::vector<std::string> split(const std::string& seq,
                               const std::string& sep = " ");  // namespace util

}  // namespace util
}  // namespace http
}  // namespace music_share

#endif  // MUS_HTTP_UTIL_H_
