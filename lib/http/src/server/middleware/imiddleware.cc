#include "http/server/middleware/imiddleware.h"

#include "http/common/request.h"  // music_share::http::common::Request
#include "http/common/response.h"  // music_share::http::common::Response

namespace music_share::http::server::middleware {

IMiddleware::IMiddleware(RequestHandler inner_handler)
    : m_inner_handler(inner_handler) {}

common::Response IMiddleware::get_response(const common::Request& request,
                                           const Parameters& params) {
    return m_inner_handler(request, params);
}

}  // namespace music_share::http::server::middleware
