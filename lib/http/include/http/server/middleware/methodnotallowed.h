#ifndef MUS_HTTP_SERVER_MIDDLEWARE_METHODNOTALLOWED_H_
#define MUS_HTTP_SERVER_MIDDLEWARE_METHODNOTALLOWED_H_

#include "http/server/middleware/imiddleware.h"

namespace music_share::http::server::middleware {

class MethodNotAllowed: public IMiddleware {
public:
    MethodNotAllowed(RequestHandler handler);
    ~MethodNotAllowed() = default;
    common::Response operator()(const common::Request& request,
                                const Parameters& params);
};

}  // namespace music_share::http::server::middleware

#endif  // MUS_HTTP_SERVER_MIDDLEWARE_METHODNOTALLOWED_H_
