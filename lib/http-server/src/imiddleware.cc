#include "http-server/imiddleware.h"

#include "http-server/request.h"  // music_share::Request
#include "http-server/response.h"  // music_share::Response
#include "http-server/exception.h"  // music_share::Exception

namespace music_share {

IMiddleware::IMiddleware(RequestHandler inner_handler,
                         std::optional<ExceptionHandler> exception_handler) 
    : m_inner_handler(inner_handler),
      m_exception_handler(exception_handler) {}

Response IMiddleware::operator()(const Request& request) {
    return call_inner_handler(request);
}

Response IMiddleware::call_inner_handler(const Request& request) {
    try {
        return m_inner_handler(request);
    } catch (const Exception& e) {
        if (m_exception_handler.has_value()) {
            return (*m_exception_handler)(request, e);
        } else {
            throw e;
        }
    }
}

}  // namespace music_share
