#ifndef MUS_INTERNAL_MUS_REPO_POSTGRES_CHAT_MESSAGE_REPOSITORY_POSTGRES_H_
#define MUS_INTERNAL_MUS_REPO_POSTGRES_CHAT_MESSAGE_REPOSITORY_POSTGRES_H_

#include "mus-irepo/ichat_message_repository.h"
#include "db_connection_postgres.h"

namespace music_share {

class ChatMessageRepositoryPostgres final : public IChatMessageRepository {
public:
    ChatMessageRepositoryPostgres(std::unique_ptr<DbConnectionPostgres> db);
    ~ChatMessageRepositoryPostgres() = default;

    std::optional<ChatMessage> Find(uint32_t id) override;
    void Insert(ChatMessage& out_chat_message) override;
    void Update(const ChatMessage& chat_message) override;
    void Delete(const ChatMessage& chat_message) override;

    std::vector<ChatMessage> FindByChatId(uint32_t chat_id) override;

private:
    std::unique_ptr<DbConnectionPostgres> m_database;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_REPO_POSTGRES_CHAT_MESSAGE_REPOSITORY_POSTGRES_H_
