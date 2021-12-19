#ifndef MUS_INTERNAL_MUS_REPO_POSTGRES_DB_UTILS_H_
#define MUS_INTERNAL_MUS_REPO_POSTGRES_DB_UTILS_H_

#include <type_traits>
#include <string>
#include <map>

namespace music_share {

using SqlObject = std::map<std::string, std::string>;

class SqlUtils {
public:
    SqlUtils() = delete;

    // Приводит value в нужный для SQL-запроса формат
    template<typename T>
    static std::string ValueToSqlFormat(const T& value) noexcept {
        if constexpr(std::is_arithmetic_v<T>) {
            return std::to_string(value);
        }
        if constexpr(std::is_same_v<T, std::string>) {
            return { "'" + value + "'" };
        }
        assert(false);
    }

    // Приводит values в строку значений в формате, нужном для SQL-запроса
    // пример, если T - std::string
    // in:  std::vector<std::string> { "test", "hello", "world" }
    // out: std::string "('test', 'hello', 'world')"
    template<typename T>
    static std::string ValuesToSqlFormat(const std::vector<T>& values,
                                         bool arrange_brackets=false) noexcept {
        if (values.empty()) {
            return { "" };
        }

        std::string result;
        if (arrange_brackets) {
            result += "(";
        }

        const T& last = *(values.crbegin());

        for (const auto& value: values) {
            result += ValueToSqlFormat(value);
            if (value != last) {
                result += ", ";
            } else {
                if (arrange_brackets) {
                    result += ")";
                }
            }
        }

        return result;
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
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_REPO_POSTGRES_DB_UTILS_H_
