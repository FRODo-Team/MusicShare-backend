#ifndef MUS_INTERNAL_MUS_REPO_POSTGRES_DATABASE_CONNECTION_POSTGRES_H_
#define MUS_INTERNAL_MUS_REPO_POSTGRES_DATABASE_CONNECTION_POSTGRES_H_

#include <iostream>
#include <pqxx/pqxx>

namespace music_share {

class DatabaseObject {
public:
    explicit DatabaseObject(const std::string& connection_string);
    DatabaseObject(const DatabaseObject&) = delete;
    virtual ~DatabaseObject() = default;

    DatabaseObject& operator=(const DatabaseObject&) = delete;

    const std::string& GetConnectionString() const { return m_connection_string; }

    virtual pqxx::result ExecuteQuery(const std::string& query);

    static std::string MakeConnectionString(const std::string& host,
                                            int port,
                                            const std::string& user,
                                            const std::string& password,
                                            const std::string& database_name,
                                            bool urlstyle = true);

protected:
    std::string m_connection_string;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_REPO_POSTGRES_DATABASE_CONNECTION_POSTGRES_H_
