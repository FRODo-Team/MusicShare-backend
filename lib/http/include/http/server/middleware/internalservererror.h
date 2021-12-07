#ifndef MUS_HTTP_SERVER_MIDDLEWARE_INTERNALSERVERERROR_H_
#define MUS_HTTP_SERVER_MIDDLEWARE_INTERNALSERVERERROR_H_

#include "http/server/middleware/imiddleware.h"

namespace music_share::http::server::middleware {

class InternalServerError: public IMiddleware {
public:
    InternalServerError(RequestHandler handler);
    ~InternalServerError() = default;
    common::Response operator()(const common::Request& request,
                                const Parameters& params);
};

}  // namespace music_share::http::server::middleware

#endif  // MUS_HTTP_SERVER_MIDDLEWARE_INTERNALSERVERERROR_H_
