#ifndef MUS_HTTP_SERVER_EXCEPTION_BADREQUEST_H_
#define MUS_HTTP_SERVER_EXCEPTION_BADREQUEST_H_

#include "http/server/exception/exception.h"

#include <string>  // std::string

namespace music_share::http::server::exception {

class BadRequest : public Exception {
public:
    BadRequest(const std::string& message)
        : Exception("Bad request: " + message) {}
};

}  // namespace music_share::http::server::exception

#endif  // MUS_HTTP_SERVER_EXCEPTION_BADREQUEST_H_
