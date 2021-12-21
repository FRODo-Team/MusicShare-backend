// Oweners: Faris Nabiev, WEB-12
#include "http/server/middleware/notfound.h"

#include "http/server/exception/notfound.h"
#include "http/common/header.h"
#include "http/common/status.h"
#include <iostream>

namespace music_share::http::server::middleware {

NotFound::NotFound(RequestHandler handler) : IMiddleware(handler) {}

common::Response NotFound::operator()(const common::Request& request,
                                      const Parameters& params) {
    try {
        return get_response(request, params);
    } catch (const exception::NotFound& e) {
        auto response = common::Response();

        response.set(common::header::content_type, "text/plain");
        response.body() = e.what();
        response.result(common::status::not_found);

        return response;
    }
}

}  // namespace music_share::http::server::middleware
