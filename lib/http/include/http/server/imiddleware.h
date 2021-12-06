#ifndef MUS_HTTP_SERVER_IMIDDLEWARE_H_
#define MUS_HTTP_SERVER_IMIDDLEWARE_H_

#include <optional>  // std::optional
#include <functional>  // std::function
#include <type_traits>  // std::is_base_of

#include "http/server/requesthandler.h"  // music_share::server::RequestHandler

namespace music_share {
namespace http {
namespace server {

class IMiddleware {
public:
    IMiddleware(RequestHandler handler);
    virtual ~IMiddleware() = default;

    virtual common::Response operator()(const common::Request& request,
                                        const Parameters& params);
protected:
    common::Response get_response(const common::Request& request,
                                  const Parameters& params);
private:
    RequestHandler m_inner_handler;
};

template<typename T>
concept Middleware = std::is_base_of<IMiddleware, T>::value;

class IMiddlewareBuilder {
public:
    virtual RequestHandler Build(RequestHandler inner_handler) = 0;
};

template<Middleware T>
class MiddlewareBuilder : public IMiddlewareBuilder {
public:
    MiddlewareBuilder() = default;
    ~MiddlewareBuilder() = default;

    RequestHandler Build(RequestHandler inner_handler) const {
        return T(inner_handler);
    }
};

}  // namespace server
}  // namespace http
}  // namespace music_share

#endif  // MUS_HTTP_SERVER_IMIDDLEWARE_H_
