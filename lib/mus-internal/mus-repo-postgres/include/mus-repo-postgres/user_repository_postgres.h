#ifndef MUS_INTERNAL_MUS_REPO_POSTGRES_USER_REPOSITORY_POSTGRES_H_
#define MUS_INTERNAL_MUS_REPO_POSTGRES_USER_REPOSITORY_POSTGRES_H_

#include <memory>

#include "mus-irepo/iuser_repository.h"
#include "db_connection_postgres.h"

namespace music_share {

class UserRepositoryPostgres final : public IUserRepository{
public:
    explicit UserRepositoryPostgres(const std::string& connection);
    ~UserRepositoryPostgres() = default;
        
    std::optional<User> Find(uint32_t id) override;
    void Insert(User& out_user) override;
    void Update(const User& user) override;
    void Delete(const User& user) override;

    std::vector<User> FindByNickname(const std::string& nickname) override;

private:
    class Mapper {
    public:
        static User ToDomain(const pqxx::row& record);
    };

    DbConnectionPostgres m_database;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_REPO_POSTGRES_USER_REPOSITORY_POSTGRES_H_
