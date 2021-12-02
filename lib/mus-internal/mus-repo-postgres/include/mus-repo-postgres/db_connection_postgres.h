#ifndef MUS_INTERNAL_MUS_REPO_POSTGRES_DATABASE_CONNECTION_POSTGRES_H_
#define MUS_INTERNAL_MUS_REPO_POSTGRES_DATABASE_CONNECTION_POSTGRES_H_

#include <iostream>
#include <pqxx/pqxx>

namespace music_share {

class DbConnectionPostgres {
public:
    explicit DbConnectionPostgres(const std::string& connection_string);
    DbConnectionPostgres(const DbConnectionPostgres&) = delete;
    virtual ~DbConnectionPostgres() = default;

    DbConnectionPostgres& operator=(const DbConnectionPostgres&) = delete;

    const std::string& GetConnectionString() const { return m_connection_string; }

    virtual pqxx::result ExecuteQuery(const std::string& query);

protected:
    std::string m_connection_string;
    pqxx::connection m_connection;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_REPO_POSTGRES_DATABASE_CONNECTION_POSTGRES_H_
