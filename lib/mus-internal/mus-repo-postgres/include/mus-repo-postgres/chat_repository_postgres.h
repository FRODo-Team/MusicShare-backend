#ifndef MUS_INTERNAL_MUS_REPO_POSTGRES_CHAT_REPOSITORY_POSTGRES_H_
#define MUS_INTERNAL_MUS_REPO_POSTGRES_CHAT_REPOSITORY_POSTGRES_H_

#include "mus-irepo/ichat_repository.h"
#include "internal/repository_postgres.h"

namespace music_share {

class ChatRepositoryPostgres final : public IChatRepository {
public:
    explicit ChatRepositoryPostgres(const std::string& connection_string);
    ChatRepositoryPostgres(const ChatRepositoryPostgres&) = delete;
    ~ChatRepositoryPostgres() = default;

    ChatRepositoryPostgres& operator=(const ChatRepositoryPostgres&) = delete;

    std::optional<Chat> Find(uint32_t id) override;
    void Insert(Chat& out_chat) override;
    void Update(const Chat& chat) override;
    void Delete(const Chat& chat) override;

    std::vector<Chat> FindByUserId(uint32_t user_id) override;
    Chat FindByIdsOfUserPair(uint32_t first_user_id,
                             uint32_t second_user_id) override;

private:
    class SqlMapper {
    public:
        static Chat ToDomainObject(const pqxx::row& row);
        static SqlObject ToSqlObject(const Chat& domain);
    };

    RepositoryPostgres<Chat, SqlMapper> m_crud_repository;
    const std::string& m_table_name;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_REPO_POSTGRES_CHAT_REPOSITORY_POSTGRES_H_
