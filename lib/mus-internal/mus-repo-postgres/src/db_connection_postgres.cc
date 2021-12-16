#include "mus-repo-postgres/db_connection_postgres.h"

namespace music_share {

DbConnectionPostgres::DbConnectionPostgres(
        const std::string& connection_string)
        :
        m_connection_string(connection_string),
        m_connection(m_connection_string) { }

pqxx::result DbConnectionPostgres::ExecuteQuery(const std::string& query) {
    // TODO(sunz): Handle Exceptions.
    pqxx::work transaction{ m_connection };
    pqxx::result response = transaction.exec(query);
    transaction.commit();
    return response;
}

} // namespace music_share
