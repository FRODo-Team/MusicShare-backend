#include "mus-repo-postgres/chat_message_repository_postgres.h"

namespace music_share {

ChatMessageRepositoryPostgres::ChatMessageRepositoryPostgres(
        const std::string& connection_string)
        :
        m_crud_repository(connection_string, "mus_chat_message"),
        m_table_name(m_crud_repository.GetTableName()) { }

std::optional<ChatMessage> ChatMessageRepositoryPostgres::Find(uint32_t id) {
    return m_crud_repository.Find(id);
}

void ChatMessageRepositoryPostgres::Insert(ChatMessage& out_obj) {
    return m_crud_repository.Insert(out_obj);
}

void ChatMessageRepositoryPostgres::Update(const ChatMessage& obj) {
    return m_crud_repository.Update(obj);
}

void ChatMessageRepositoryPostgres::Delete(const ChatMessage& obj) {
    return m_crud_repository.Delete(obj);
}

std::vector<ChatMessage> ChatMessageRepositoryPostgres::FindByChatId(
        uint32_t chat_id)
{
    std::string query =
            "SELECT * FROM " + m_table_name + " " +
            "WHERE chat_id=" + SqlUtils::ValueToSqlFormat(chat_id);

    pqxx::result response = m_crud_repository.ExecuteQuery(query);

    std::vector<ChatMessage> result;
    for (const auto& row: response) {
        ChatMessage cm = SqlMapper::ToDomainObject(row);
        result.push_back(cm);
    }

    return result;
}

ChatMessage ChatMessageRepositoryPostgres::SqlMapper::ToDomainObject(
        const pqxx::row &row)
{
    uint32_t id;
    uint32_t sender_id;
    std::string datetime;
    std::string content;
    uint32_t chat_id;

    for (const auto& field: row) {
        if (field.name() == std::string{ "id" }) {
            id = field.as<uint32_t>();
        } else if (field.name() == std::string{ "sender_id" }) {
            sender_id = field.as<uint32_t>();
        } else if (field.name() == std::string{ "datetime" }) {
            datetime = field.as<std::string>();
        } else if (field.name() == std::string{ "content" }) {
            content = field.as<std::string>();
        } else if (field.name() == std::string{ "chat_id" }) {
            chat_id = field.as<uint32_t>();
        }
    }

    return { sender_id, datetime, content, chat_id, id };
}

SqlObject ChatMessageRepositoryPostgres::SqlMapper::ToSqlObject(
        const ChatMessage& domain)
{
    SqlObject result;

    result["sender_id"] = SqlUtils::ValueToSqlFormat(domain.GetSenderId());
    result["datetime"] = SqlUtils::ValueToSqlFormat(domain.GetDatetime());
    result["content"] = SqlUtils::ValueToSqlFormat(domain.GetContent());
    result["chat_id"] = SqlUtils::ValueToSqlFormat(domain.GetChatId());
    if (domain.GetId().has_value()) {
        result["id"] = SqlUtils::ValueToSqlFormat(domain.GetId().value());
    }
}

} // namespace music_share
