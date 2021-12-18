#include "config-parser/config.h"

#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <fstream>

namespace music_share::config_parser {

Config::Config(std::string_view base_name) {
    std::string active_profile;
    std::string profile_env_name = "_ACTIVE_PROFILE";

    std::transform(base_name.begin(), base_name.end(),
                   std::inserter(profile_env_name,
                                 profile_env_name.begin()),
                   [](char c) { return std::toupper(c); });

    if (const char* active_profile_ =
            std::getenv(profile_env_name.c_str())) {
        active_profile = active_profile_;
    }

    std::stringstream config_name_builder;
    config_name_builder
        << base_name
        << (active_profile != "" ? "-" : "")
        << active_profile
        << ".json";
    std::string config_name = config_name_builder.str();

    std::ifstream config_file(config_name);
    config_file >> m_json;
}

Config Config::FromJson(nlohmann::json j) {
    Config conf;
    conf.m_json = j;
    return conf;
}

} // namespace music_share::config_parser
