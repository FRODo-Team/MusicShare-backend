#include "mus-repo-postgres/chat_message_repository_postgres.h"

namespace music_share {

ChatMessageRepositoryPostgres::ChatMessageRepositoryPostgres(
        const std::string& connection)
        : m_database(connection) {
    throw std::runtime_error("Not implemented yet");
}

std::optional<ChatMessage> ChatMessageRepositoryPostgres::Find(uint32_t id) {
    throw std::runtime_error("Not implemented yet");
}

void ChatMessageRepositoryPostgres::Insert(ChatMessage& out_chat_message) {
    throw std::runtime_error("Not implemented yet");
}

void ChatMessageRepositoryPostgres::Update(const ChatMessage& chat_message) {
    throw std::runtime_error("Not implemented yet");
}

void ChatMessageRepositoryPostgres::Delete(const ChatMessage& chat_message) {
    throw std::runtime_error("Not implemented yet");
}

std::vector<ChatMessage> ChatMessageRepositoryPostgres::FindByChatId(
        uint32_t chat_id) {
    throw std::runtime_error("Not implemented yet");
}


ChatMessage ChatMessageRepositoryPostgres::Mapper::ToDomain(
        const pqxx::row& record) {
    throw std::runtime_error("Not implemented yet");
}

} // namespace music_share
