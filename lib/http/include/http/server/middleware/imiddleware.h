#ifndef MUS_HTTP_SERVER_MIDDLEWARE_IMIDDLEWARE_H_
#define MUS_HTTP_SERVER_MIDDLEWARE_IMIDDLEWARE_H_

#include <optional>  // std::optional
#include <functional>  // std::function
#include <type_traits>  // std::is_base_of

#include "http/server/requesthandler.h"  // music_share::server::RequestHandler

namespace music_share::http::server::middleware {

class IMiddleware {
public:
    IMiddleware(RequestHandler handler);
    virtual ~IMiddleware() = default;

    virtual common::Response operator()(const common::Request& request,
                                        const Parameters& params) = 0;
protected:
    common::Response get_response(const common::Request& request,
                                  const Parameters& params);
private:
    RequestHandler m_inner_handler;
};

}  // namespace music_share::http::server::middleware

#endif  // MUS_HTTP_SERVER_MIDDLEWARE_IMIDDLEWARE_H_
