// Owners: Rostislav Vivcharuk, WEB-12
#ifndef MUS_INTERNAL_MUS_REPO_POSTGRES_CHAT_MESSAGE_REPOSITORY_POSTGRES_H_
#define MUS_INTERNAL_MUS_REPO_POSTGRES_CHAT_MESSAGE_REPOSITORY_POSTGRES_H_

#include "mus-irepo/ichat_message_repository.h"
#include "internal/repository_postgres.h"

namespace music_share {

class ChatMessageRepositoryPostgres final : public IChatMessageRepository {
public:
    explicit ChatMessageRepositoryPostgres(const std::string& connection_string);
    ChatMessageRepositoryPostgres(const ChatMessageRepositoryPostgres&) = delete;
    ~ChatMessageRepositoryPostgres() = default;

    ChatMessageRepositoryPostgres& operator=(const ChatMessageRepositoryPostgres&) = delete;

    std::optional<ChatMessage> Find(uint32_t id) override;
    void Insert(ChatMessage& out_obj) override;
    void Update(const ChatMessage& obj) override;
    void Delete(const ChatMessage& obj) override;

    std::vector<ChatMessage> FindByChatId(uint32_t chat_id) override;
    std::vector<ChatMessage> FindByUserId(
            uint32_t user_id,
            std::optional<std::string> since_datetime) override;

private:
    class SqlMapper {
    public:
        static ChatMessage ToDomainObject(const pqxx::row& row);
        static SqlObject ToSqlObject(const ChatMessage& domain);
    };

    RepositoryPostgres<ChatMessage, SqlMapper> m_crud_repository;

    const std::string& m_table_name;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_REPO_POSTGRES_CHAT_MESSAGE_REPOSITORY_POSTGRES_H_
