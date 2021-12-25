// Owners: Faris Nabiev, WEB-12
#ifndef MUS_HTTP_SERVER_MIDDLEWARE_MIDDLEWARE_H_
#define MUS_HTTP_SERVER_MIDDLEWARE_MIDDLEWARE_H_

#include "http/server/middleware/imiddleware.h"

namespace music_share::http::server::middleware {

template<typename T>
concept Middleware = std::is_base_of<IMiddleware, T>::value;

class IMiddlewareBuilder {
public:
    virtual ~IMiddlewareBuilder() = default;

    virtual RequestHandler Build(RequestHandler inner_handler) const = 0;
};

template<Middleware T>
class MiddlewareBuilder : public IMiddlewareBuilder {
public:
    MiddlewareBuilder() = default;
    ~MiddlewareBuilder() = default;

    RequestHandler Build(RequestHandler inner_handler) const {
        return T(inner_handler);
    }

    static std::shared_ptr<MiddlewareBuilder<T>> Create() {
        return std::make_shared<MiddlewareBuilder<T>>();
    }
};

}  // namespace music_share::http::server::middleware

#endif  // MUS_HTTP_SERVER_MIDDLEWARE_MIDDLEWARE_H_
