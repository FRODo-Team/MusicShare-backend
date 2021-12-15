#ifndef MUS_HTTP_COMMON_RESPONSE_H_
#define MUS_HTTP_COMMON_RESPONSE_H_

#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>

namespace music_share {
namespace http {
namespace common {

using Response = boost::beast::http::response<boost::beast::http::string_body>;

}  // namespace common
}  // namespace http
}  // namespace music_share

#endif  // MUS_HTTP_COMMON_RESPONSE_H_
