// Oweners: Faris Nabiev, WEB-12
#ifndef MUS_HTTP_COMMON_REQUEST_H_
#define MUS_HTTP_COMMON_REQUEST_H_

#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>

#include <string>  // std::string

namespace music_share {
namespace http {
namespace common {

using Request = boost::beast::http::request<boost::beast::http::string_body>;

}  // namespace common
}  // namespace http
}  // namespace music_share

#endif  // MUS_HTTP_COMMON_REQUEST_H_
