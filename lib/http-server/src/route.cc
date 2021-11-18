#include "http-server/route.h"

#include <cstring>

#include "http-server/imiddleware.h"

namespace music_share {

Route::Route(const std::string& path, RequestHandler handler,
             std::initializer_list<std::shared_ptr<IMiddlewareBuilder>>
             middleware_builders)
    : m_path(path),
      m_handler(handler),
      m_middleware_builders(middleware_builders) {}

std::string Route::GetPath() const {
    return m_path;
}

RequestHandler Route::GetHandler() {
    RequestHandler handler = m_handler;

    for (auto it = m_middleware_builders.rbegin();
         it != m_middleware_builders.rend(); ++it) {
        handler = (*it)->Build(handler);
    }

    return handler;
}

}  // namespace music_share
