// Oweners: Faris Nabiev, WEB-12
#ifndef MUS_HTTP_SERVER_EXCEPTION_NOTFOUND_H_
#define MUS_HTTP_SERVER_EXCEPTION_NOTFOUND_H_

#include "http/server/exception/exception.h"

#include <string>  // std::string

namespace music_share::http::server::exception {

class NotFound : public Exception {
public:
    NotFound(const std::string& path)
        : Exception("Can't find resource for path: " + path),
          m_path(path) {}

    inline const std::string& Path() const { return m_path; }
private:
    std::string m_path;
};

}  // namespace music_share::http::server::exception

#endif  // MUS_HTTP_SERVER_EXCEPTION_NOTFOUND_H_
