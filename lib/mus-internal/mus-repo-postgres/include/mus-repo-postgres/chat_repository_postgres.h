#ifndef MUS_INTERNAL_MUS_REPO_POSTGRES_CHAT_REPOSITORY_POSTGRES_H_
#define MUS_INTERNAL_MUS_REPO_POSTGRES_CHAT_REPOSITORY_POSTGRES_H_

#include "mus-irepo/ichat_repository.h"
#include "db_connection_postgres.h"

namespace music_share {

class ChatRepositoryPostgres final : public IChatRepository {
    ChatRepositoryPostgres(std::unique_ptr<DbConnectionPostgres> db);
    ~ChatRepositoryPostgres() = default;

    std::optional<Chat> Find(uint32_t id) override;
    void Insert(Chat& out_chat) override;
    void Update(const Chat& chat) override;
    void Delete(const Chat& chat) override;

    std::vector<Chat> FindByUserId(uint32_t user_id) override;

    Chat FindByIdsOfUserPair(uint32_t first_user_id,
                             uint32_t second_user_id) override;

private:
    std::unique_ptr<DbConnectionPostgres> m_database;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_REPO_POSTGRES_CHAT_REPOSITORY_POSTGRES_H_
