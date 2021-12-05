#ifndef MUS_HTTP_COMMON_REQUEST_H_
#define MUS_HTTP_COMMON_REQUEST_H_

#include "http/common/message.h"  // http::common::Message

#include <string>  // std::string

namespace music_share {
namespace http {
namespace common {

class Request : public Message {
public:
    std::string Method() const;
    std::string Path() const;
private:
};

}  // namespace common
}  // namespace http
}  // namespace music_share

#endif  // MUS_HTTP_COMMON_REQUEST_H_
