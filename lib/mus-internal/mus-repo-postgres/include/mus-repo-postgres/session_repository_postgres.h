// Owners: Rostislav Vivcharuk, WEB-12
#ifndef MUS_INTERNAL_MUS_REPO_POSTGRES_SESSION_REPOSITORY_POSTGRES_H_
#define MUS_INTERNAL_MUS_REPO_POSTGRES_SESSION_REPOSITORY_POSTGRES_H_

#include "mus-irepo/isession_repository.h"
#include "mus-repo-postgres/internal/repository_postgres.h"

namespace music_share {

class SessionRepositoryPostgres : public ISessionRepository {
public:
    explicit SessionRepositoryPostgres(const std::string& connection_string);
    SessionRepositoryPostgres(const SessionRepositoryPostgres&) = delete;
    ~SessionRepositoryPostgres() override = default;

    SessionRepositoryPostgres& operator=(const SessionRepositoryPostgres&) = delete;

    std::optional<Session> Find(uint32_t id) override;
    void Insert(Session& out_obj) override;
    void Update(const Session& obj) override;
    void Delete(const Session& obj) override;

    std::optional<Session> FindBySessionKey(const std::string& key) override;

private:
    class SqlMapper {
    public:
        static Session ToDomainObject(const pqxx::row& row);
        static SqlObject ToSqlObject(const Session& domain);
    };

    RepositoryPostgres<Session, SqlMapper> m_crud_repository;
    const std::string m_table_name;

    static constexpr std::string_view kTableName = "mus_session";
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_REPO_POSTGRES_SESSION_REPOSITORY_POSTGRES_H_
