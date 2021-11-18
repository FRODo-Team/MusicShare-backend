#ifndef MUS_MUSINTERNAL_MUSCONTROLLER_REQUEST_H_
#define MUS_MUSINTERNAL_MUSCONTROLLER_REQUEST_H_

#include <map>  // std::map
#include <string>  // std::string
#include <optional>  // std::optional

namespace music_share {

template <typename Body>
struct Request {
    enum class Method {
        GET, POST, PATCH, DELETE
    };

    Method method;
    std::map<std::string, std::string> parameters;
    std::map<std::string, std::string> headers;
    std::optional<Body> body;
};

}  // namespace music_share

#endif  // MUS_MUSINTERNAL_MUSCONTROLLER_REQUEST_H_
