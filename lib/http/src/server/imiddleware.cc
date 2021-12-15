#include "http/server/imiddleware.h"

#include "http/common/request.h"  // music_share::http::common::Request
#include "http/common/response.h"  // music_share::http::common::Response
#include "http/server/exception.h"  // music_share::http::server::Exception

namespace music_share {
namespace http {
namespace server {

IMiddleware::IMiddleware(RequestHandler inner_handler)
    : m_inner_handler(inner_handler) {}

common::Response IMiddleware::operator()(const common::Request& request,
                                         const Parameters& params) {
    return get_response(request, params);
}

common::Response IMiddleware::get_response(const common::Request& request,
                                           const Parameters& params) {
    return m_inner_handler(request, params);
}

}  // namespace server
}  // namespace http
}  // namespace music_share
