#ifndef MUS_HTTPSERVER_IMIDDLEWARE_H_
#define MUS_HTTPSERVER_IMIDDLEWARE_H_

#include <optional>  // std::optional
#include <functional>  // std::function
#include <type_traits>  // std::is_base_of

#include "http-server//requesthandler.h"  // music_share::RequestHandler

namespace music_share {
namespace http_server {

class IMiddleware {
public:
    IMiddleware(RequestHandler handler);
    virtual ~IMiddleware() = default;

    virtual Response operator()(const Request& request);
protected:
    Response get_response(const Request& request);
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

}  // namespace http_server
}  // namespace music_share

#endif  // MUS_HTTPSERVER_IMIDDLEWARE_H_
