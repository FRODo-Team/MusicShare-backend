// Owners: Rostislav Vivcharuk, WEB-12
#include "mus-repo-postgres/internal/database_object.h"

namespace music_share {

DatabaseObject::DatabaseObject(
        const std::string& connection_string)
        :
        m_connection_string(connection_string) { }

pqxx::result DatabaseObject::ExecuteQuery(const std::string& query) {
    // TODO(sunz): Handle Exceptions.
    pqxx::connection connection(m_connection_string);
    pqxx::work transaction{ connection };
    pqxx::result response = transaction.exec(query);
    transaction.commit();
    return response;
}

std::string DatabaseObject::MakeConnectionString(const std::string& host,
                                                 int port,
                                                 const std::string& user,
                                                 const std::string& password,
                                                 const std::string& database_name,
                                                 bool urlstyle)
{
    if (urlstyle) {
        return {
                "postgresql://" + user + ":" + password +"@" + host + ":" +
                std::to_string(port) + "/" + database_name
        };
    }

    return {
            "host=" + host + " " +
            "port=" + std::to_string(port) + " " +
            "dbname=" + database_name + " " +
            "user=" + user + " " +
            "password=" + password
    };
}

} // namespace music_share
