#ifndef MUS_HTTP_SERVER_REQUESTHANDLER_H_
#define MUS_HTTP_SERVER_REQUESTHANDLER_H_

#include <functional>  // std::function

namespace music_share {
namespace http {

namespace common {

class Request;
class Response;

}  // namespace common

namespace server {

using RequestHandler = std::function<common::Response(const common::Request&)>;

}  // namespace server
}  // namespace http
}  // namespace music_share

#endif  // MUS_HTTP_SERVER_REQUESTHANDLER_H_
