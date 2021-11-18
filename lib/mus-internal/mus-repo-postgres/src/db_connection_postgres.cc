#include <mus-repo-postgres/db_connection_postgres.h>

namespace music_share {

DbConnectionPostgres::DbConnectionPostgres(
    const std::string& connection_string)
    : m_connection_string(connection_string)
{ }

const std::string& DbConnectionPostgres::GetConnectionString() const {
    return m_connection_string;
}

pqxx::result DbConnectionPostgres::ExecuteQuery(
    const std::string& sql_command) {
    throw std::runtime_error("Not implemented yet");
}

void DbConnectionPostgres::ValidateConnection(
    const std::string& table_name) {
    throw std::runtime_error("Not implemented yet");
}

void DbConnectionPostgres::ValidateConnection(
    const std::vector<std::string>& table_names) {
    for (auto table_name: table_names) {
        ValidateConnection(table_name);
    }
}

} // namespace music_share
