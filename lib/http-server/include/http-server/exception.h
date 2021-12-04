#ifndef MUS_HTTPSERVER_EXCEPTION_H_
#define MUS_HTTPSERVER_EXCEPTION_H_

#include <exception>

namespace music_share {
namespace http_server {

class Exception : public std::exception {
};

}  // namespace http_server
}  // namespace music_share

#endif  // MUS_HTTPSERVER_EXCEPTION_H_
