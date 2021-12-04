#include "http-server/imiddleware.h"

#include "http-server/request.h"  // music_share::Request
#include "http-server/response.h"  // music_share::Response
#include "http-server/exception.h"  // music_share::Exception

namespace music_share {
namespace http_server {

IMiddleware::IMiddleware(RequestHandler inner_handler)
    : m_inner_handler(inner_handler) {}

Response IMiddleware::operator()(const Request& request) {
    return get_response(request);
}

Response IMiddleware::get_response(const Request& request) {
    return m_inner_handler(request);
}

}  // namespace http_server
}  // namespace music_share
