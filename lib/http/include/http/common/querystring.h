// Owners: Faris Nabiev, WEB-12
#ifndef MUS_HTTP_COMMON_QUERYSTRING_H_
#define MUS_HTTP_COMMON_QUERYSTRING_H_

#include <map>  // std::multimap
#include <string>  // std::string

namespace music_share::http::common {

class QueryString {
public:
    inline void Append(const std::string& key, const std::string& value) {
        m_entries.emplace(key, value);
    }

    inline const auto& Entries() const { return m_entries; };

    inline size_t Size() { return m_entries.size(); }

    inline auto Get(const std::string& key) {
        return m_entries.find(key);
    }
    inline auto GetAll(const std::string key) {
        return m_entries.equal_range(key);
    }

    std::string toString() const;
    static QueryString fromString(const std::string& data);
private:
    static std::string encode(const std::string& value);
    static std::string decode(const std::string& value);

    std::multimap<std::string, std::string> m_entries;
};

}  // namespace music_share::http::common

#endif  // MUS_HTTP_COMMON_QUERYSTRING_H_
