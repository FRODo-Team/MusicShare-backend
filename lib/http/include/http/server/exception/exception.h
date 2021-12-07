#ifndef MUS_HTTP_SERVER_EXCEPTION_EXCEPTION_H_
#define MUS_HTTP_SERVER_EXCEPTION_EXCEPTION_H_

#include <exception>

#include <string>  // std::string

namespace music_share::http::server::exception {

class Exception : public std::exception {
public:
    Exception(const std::string& message) : m_message(message) {}
    virtual ~Exception() = default;

    virtual const char* what() const noexcept {
        return m_message.c_str();
    }
protected:
    std::string m_message;
};

}  // namespace music_share::http::server::exception

#endif  // MUS_HTTP_SERVER_EXCEPTION_EXCEPTION_H_
