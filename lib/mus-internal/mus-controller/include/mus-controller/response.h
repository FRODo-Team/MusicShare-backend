#ifndef MUS_MUSINTERNAL_MUSCONTROLLER_RESPONSE_H_
#define MUS_MUSINTERNAL_MUSCONTROLLER_RESPONSE_H_

#include <map>  // std::map
#include <string>  // std::string
#include <optional>  // std::optional

namespace music_share {

template <typename Body>
struct Response {
    std::map<std::string, std::string> headers;
    std::optional<Body> body;
};

}  // namespace music_share

#endif  // MUS_MUSINTERNAL_MUSCONTROLLER_RESPONSE_H_
