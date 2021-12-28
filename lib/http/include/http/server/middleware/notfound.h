// Oweners: Faris Nabiev, WEB-12
#ifndef MUS_HTTP_SERVER_MIDDLEWARE_NOTFOUND_H_
#define MUS_HTTP_SERVER_MIDDLEWARE_NOTFOUND_H_

#include "http/server/middleware/imiddleware.h"

namespace music_share::http::server::middleware {

class NotFound: public IMiddleware {
public:
    NotFound(RequestHandler handler);
    ~NotFound() = default;
    common::Response operator()(const common::Request& request,
                                const Parameters& params) override;
};

}  // namespace music_share::http::server::middleware

#endif  // MUS_HTTP_SERVER_MIDDLEWARE_NOTFOUND_H_
