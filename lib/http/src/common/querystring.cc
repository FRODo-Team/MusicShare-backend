// Oweners: Faris Nabiev, WEB-12
#include "http/common/querystring.h"

#include <cctype>
#include <sstream>
#include <iomanip>

#include "util.h"

namespace music_share::http::common {

QueryString QueryString::fromString(const std::string& data) {
    QueryString qs;
    auto param_list = util::split(data, "&");

    for (const auto& key_value: param_list) {
        size_t kv_divider_pos = key_value.find('=');

        auto key = key_value.substr(0, kv_divider_pos);
        auto value = key_value.substr(kv_divider_pos + 1);

        qs.Append(key, decode(value));
    }

    return qs;
}

std::string QueryString::toString() const {
    std::stringstream ss;

    size_t i = 0;
    for (const auto& [key, value]: m_entries) {
        if ((i++) != 0) {
            ss << '&';
        }

        ss << key;
        if (value != "") {
            ss << '=' << encode(value);
        }
    }

    return ss.str().c_str();
}

std::string QueryString::encode(const std::string& value) {
    std::stringstream encoded;

    for (char c: value) {
        if (isalnum(c) || c == '~' || c == '-' ||
                   c == '.' || c == '_') {
            encoded << c;
        } else {
            encoded << "%" <<
                    std::setw(2) << std::setfill('0') <<
                    std::hex << (unsigned int)c <<
                    std::setw(1);
        }
    }

    return encoded.str();
}

std::string QueryString::decode(const std::string& value) {
    std::stringstream encoded;
    std::stringstream decoded;

    char c = 0;
    encoded << value;
    while (encoded >> c) {
        if (c == '+') {
            decoded << ' ';
        } else if (c == '%') {
            unsigned int chr;
            char hi, lo;
            std::stringstream ss;

            encoded >> hi >> lo;
            ss << hi << lo;

            ss >> std::hex >> chr;
            decoded << (char)chr;
        } else {
            decoded << c;
        }
    }

    return decoded.str();
}

}  // namespace music_share::http::common
