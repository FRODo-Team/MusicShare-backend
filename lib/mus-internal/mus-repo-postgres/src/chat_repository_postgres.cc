#include "mus-repo-postgres/chat_repository_postgres.h"

namespace music_share {

ChatRepositoryPostgres::ChatRepositoryPostgres(
        std::unique_ptr<DbConnectionPostgres> db)
        : m_database(std::move(db)) {
    throw std::runtime_error("Not implemented yet");
}

std::optional<Chat> ChatRepositoryPostgres::Find(uint32_t id) {
    throw std::runtime_error("Not implemented yet");
}

void ChatRepositoryPostgres::Insert(Chat& out_chat) {
    throw std::runtime_error("Not implemented yet");
}

void ChatRepositoryPostgres::Update(const Chat& chat) {
    throw std::runtime_error("Not implemented yet");
}

void ChatRepositoryPostgres::Delete(const Chat& chat) {
    throw std::runtime_error("Not implemented yet");
}

std::vector<Chat> ChatRepositoryPostgres::FindByUserId(uint32_t user_id) {
    throw std::runtime_error("Not implemented yet");
}

Chat ChatRepositoryPostgres::FindByIdsOfUserPair(uint32_t first_user_id,
                                                 uint32_t second_user_id) {
    throw std::runtime_error("Not implemented yet");
}

} // namespace music_share
