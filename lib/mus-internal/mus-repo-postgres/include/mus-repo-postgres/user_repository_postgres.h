// Owners: Rostislav Vivcharuk, WEB-12
#ifndef MUS_INTERNAL_MUS_REPO_POSTGRES_USER_REPOSITORY_POSTGRES_H_
#define MUS_INTERNAL_MUS_REPO_POSTGRES_USER_REPOSITORY_POSTGRES_H_

#include "mus-irepo/iuser_repository.h"
#include "mus-repo-postgres/internal/repository_postgres.h"

namespace music_share {

class UserRepositoryPostgres final : public IUserRepository {
public:
    explicit UserRepositoryPostgres(const std::string& connection_string);
    UserRepositoryPostgres(const UserRepositoryPostgres&) = delete;
    ~UserRepositoryPostgres() = default;

    UserRepositoryPostgres& operator=(const UserRepositoryPostgres&) = delete;

    std::optional<User> Find(uint32_t id) override;
    void Insert(User& out_obj) override;
    void Update(const User& obj) override;
    void Delete(const User& obj) override;

    std::vector<User> FetchAll(std::optional<uint32_t> limit={ }) override;
    std::optional<User> FindByUsername(const std::string& username) override;
    std::optional<User> FindByEmail(const std::string& email) override;
    std::vector<User> FindByNickname(const std::string& nickname) override;

private:
    class SqlMapperForUserTable {
    public:
        static User ToDomainObject(const pqxx::row& row);
        static SqlObject ToSqlObject(const User& domain);
    };

    RepositoryPostgres<User, SqlMapperForUserTable> m_crud_repository;
    const std::string& m_table_name;

    static constexpr std::string_view kUserHasPlaylistTableName =
            "mus_user_has_playlist";
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_REPO_POSTGRES_USER_REPOSITORY_POSTGRES_H_
