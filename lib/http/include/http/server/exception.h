#ifndef MUS_HTTP_SERVER_EXCEPTION_H_
#define MUS_HTTP_SERVER_EXCEPTION_H_

#include <exception>

namespace music_share {
namespace http {
namespace server {

class Exception : public std::exception {
};

}  // namespace server
}  // namespace http
}  // namespace music_share

#endif  // MUS_HTTP_SERVER_EXCEPTION_H_
