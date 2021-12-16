#ifndef MUS_INTERNAL_MUS_REPO_POSTGRES_DB_UTILS_H_
#define MUS_INTERNAL_MUS_REPO_POSTGRES_DB_UTILS_H_

#include <type_traits>
#include <string>
#include <map>

namespace music_share {

using SqlObject = std::map<std::string, std::string>;

class DbUtils {
public:
    DbUtils() = delete;

    // Приводит value в нужный для SQL-запроса формат
    template<typename T>
    static std::string ValueToSqlFormat(const T& value) noexcept {
        if constexpr(std::is_arithmetic_v<T>) {
            return std::to_string(value);
        }
        if constexpr(std::is_same_v<T, std::string>) {
            return { "'" + value + "'" };
        }
    }

    static std::pair<std::string, std::string> SqlObjectToQueryableInsertStrings(
            const SqlObject& sql_obj)
    {
        std::string attributes = "(";
        std::string values = "(";

        const std::string& last = sql_obj.crbegin()->first;

        for (const auto& [attr, value]: sql_obj) {
            attributes += attr;
            values += value;
            if (attr != last) {
                attributes += ", ";
                values += ", ";
            }
        }

        attributes += ")";
        values += ")";

        return std::make_pair(attributes, values);
    }

    static std::string SqlObjectToQueryableUpdateString(
            const SqlObject& sql_obj)
    {
        std::string result;

        const std::string& last = sql_obj.crbegin()->first;

        for (const auto& [attr, value]: sql_obj) {
            result += attr + " = " + value;
            if (attr != last) {
                result += ", ";
            }
        }

        return result;
    }

    static std::string MakeConnectionString(const std::string& host,
                                            int port,
                                            const std::string& user,
                                            const std::string& password,
                                            const std::string& database_name)
    {
        /*return {
            "postgresql://" + user + ":" + password +"@" + host + ":" +
             std::to_string(port) + "/" + database_name
        };*/

        return {
            "host=" + host + " " +
            "port=" + std::to_string(port) + " " +
            "dbname=" + database_name + " " +
            "user=" + user + " " +
            "password=" + password
        };
    }
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_REPO_POSTGRES_DB_UTILS_H_
