#ifndef MUS_HTTP_SERVER_EXCEPTION_METHODNOTALLOWED_H_
#define MUS_HTTP_SERVER_EXCEPTION_METHODNOTALLOWED_H_

#include "http/server/exception/exception.h"

#include <string>  // std::string

namespace music_share::http::server::exception {

class MethodNotAllowed : public Exception {
public:
    MethodNotAllowed(const std::string& method, const std::string& path)
        : Exception("Method '" + method +
                    "' is not allowed for path: " + path),
          m_method(method),
          m_path(path) {}

    inline std::string Method() const { return m_method; }
    inline std::string Path() const { return m_path; }
private:
    std::string m_method;
    std::string m_path;
};

}  // namespace music_share::http::server::exception

#endif  // MUS_HTTP_SERVER_EXCEPTION_METHODNOTALLOWED_H_
