#include "http/server/middleware/methodnotallowed.h"

#include "http/server/exception/methodnotallowed.h"
#include "http/common/header.h"
#include "http/common/status.h"

namespace music_share::http::server::middleware {

MethodNotAllowed::MethodNotAllowed(RequestHandler handler)
    : IMiddleware(handler) {}

common::Response MethodNotAllowed::operator()(const common::Request& request,
                                              const Parameters& params) {
    try {
        return get_response(request, params);
    } catch (const exception::MethodNotAllowed& e) {
        auto response = common::Response();

        response.set(common::header::content_type, "text/plain");
        response.body() = e.what();
        response.result(common::status::method_not_allowed);

        return response;
    }
}

}  // namespace music_share::http::server::middleware
