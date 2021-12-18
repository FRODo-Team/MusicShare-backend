#ifndef MUS_CONFIGPARSER_CONFIG_H_
#define MUS_CONFIGPARSER_CONFIG_H_

#include <string>
#include <nlohmann/json.hpp>

namespace music_share::config_parser {

class Config {
public:
    explicit Config(std::string_view base_name);
    ~Config() = default;

    template<typename T>
    T Get() {
        return m_json.get<T>();
    }

    Config operator[](std::string_view key) {
        return Config::FromJson(m_json[key.data()]);
    }
private:
    Config() = default;
    static Config FromJson(nlohmann::json j);

    nlohmann::json m_json;
};

} // namespace music_share::config_parser

#endif  // MUS_CONFIGPARSER_CONFIG_H_
