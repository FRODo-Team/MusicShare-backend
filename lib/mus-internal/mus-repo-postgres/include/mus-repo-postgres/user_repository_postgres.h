#ifndef MUS_INTERNAL_MUS_REPO_POSTGRES_USER_REPOSITORY_POSTGRES_H_
#define MUS_INTERNAL_MUS_REPO_POSTGRES_USER_REPOSITORY_POSTGRES_H_

#include "mus-irepo/iuser_repository.h"
#include "db_connection_postgres.h"
#include "db_utils.h"

namespace music_share {

class UserRepositoryPostgres final : public IUserRepository {
public:
    explicit UserRepositoryPostgres(const std::string& connection);
    ~UserRepositoryPostgres() = default;
        
    std::optional<User> Find(uint32_t id) override;
    void Insert(User& out_user) override;
    void Update(const User& user) override;
    void Delete(const User& user) override;

    std::vector<User> FindByNickname(const std::string& nickname) override;
    std::optional<User> FindByUsername(const std::string& username) override;
    std::optional<User> FindByEmail(const std::string& email) override;

private:
    DbConnectionPostgres m_database;

    class Mapper {
    public:
        static User ToDomainObject(const pqxx::row& record);
        static SqlObject ToSqlObject(const User& domain_obj);
    };

    static constexpr std::string_view kTableName = "mus_user";
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_REPO_POSTGRES_USER_REPOSITORY_POSTGRES_H_
