// Oweners: Faris Nabiev, WEB-12
#include "http/server/middleware/internalservererror.h"

#include <exception>

#include "http/common/header.h"
#include "http/common/status.h"

namespace music_share::http::server::middleware {

InternalServerError::InternalServerError(RequestHandler handler)
    : IMiddleware(handler) {}

common::Response InternalServerError::operator()(const common::Request& request,
                                                 const Parameters& params) {
    try {
        return get_response(request, params);
    } catch (const std::exception& e) {
        auto response = common::Response();

        response.set(common::header::content_type, "text/plain");
        response.body() = e.what();
        response.result(common::status::internal_server_error);

        return response;
    }
}

}  // namespace music_share::http::server::middleware
