#ifndef MUS_HTTPSERVER_IMIDDLEWARE_H_
#define MUS_HTTPSERVER_IMIDDLEWARE_H_

#include <optional>  // std::optional
#include <functional>  // std::function
#include <type_traits>  // std::is_base_of

#include "http-server//requesthandler.h"  // music_share::RequestHandler

namespace music_share {

class Exception;

class IMiddleware {
public:
    using ExceptionHandler = std::function<Response(const Request&,
                                                    const Exception&)>;

    IMiddleware(RequestHandler inner_handler,
                std::optional<ExceptionHandler> exception_handler);
    virtual ~IMiddleware() = default;

    virtual Response operator()(const Request& request);
protected:
    Response call_inner_handler(const Request& request);
private:
    RequestHandler m_inner_handler;
    std::optional<ExceptionHandler> m_exception_handler;
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
    explicit MiddlewareBuilder(
        std::optional<IMiddleware::ExceptionHandler> exception_handler) 
        : m_exception_handler(exception_handler) {}
    ~MiddlewareBuilder() = default;

    RequestHandler Build(RequestHandler inner_handler) {
        return T(inner_handler, m_exception_handler);
    }
private:
    std::optional<IMiddleware::ExceptionHandler> m_exception_handler;
};

}  // namespace music_share

#endif  // MUS_HTTPSERVER_IMIDDLEWARE_H_
