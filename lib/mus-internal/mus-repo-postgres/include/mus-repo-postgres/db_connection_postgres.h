#ifndef MUS_INTERNAL_MUS_REPO_POSTGRES_DATABASE_CONNECTION_POSTGRES_H_
#define MUS_INTERNAL_MUS_REPO_POSTGRES_DATABASE_CONNECTION_POSTGRES_H_

#include <iostream>
#include <pqxx/pqxx>

namespace music_share {

class DbConnectionPostgres {
public:
    explicit DbConnectionPostgres(const std::string& connection);
    virtual ~DbConnectionPostgres() = default;

    const std::string& GetConnectionString() const;

    virtual pqxx::result ExecuteQuery(const std::string& sql_command);
    virtual void ValidateConnection(const std::string& table_name);
    virtual void ValidateConnection(const std::vector<std::string>& table_names);

protected:

    std::string m_connection_string;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_REPO_POSTGRES_DATABASE_CONNECTION_POSTGRES_H_
