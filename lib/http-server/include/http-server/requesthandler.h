#ifndef MUS_HTTPSERVER_REQUESTHANDLER_H_
#define MUS_HTTPSERVER_REQUESTHANDLER_H_

#include <functional>  // std::function

namespace music_share {

struct Request;
struct Response;

using RequestHandler = std::function<Response(const Request&)>;

}  // namespace music_share

#endif  // MUS_HTTPSERVER_REQUESTHANDLER_H_
