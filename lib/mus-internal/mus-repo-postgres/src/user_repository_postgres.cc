#include "mus-repo-postgres/user_repository_postgres.h"

namespace music_share {

UserRepositoryPostgres::UserRepositoryPostgres(const std::string& connection)
        : m_database(connection) {
    throw std::runtime_error("Not implemented yet");
}

std::optional<User> UserRepositoryPostgres::Find(uint32_t id) {
    throw std::runtime_error("Not implemented yet");
}

void UserRepositoryPostgres::Insert(User& out_user) {
    throw std::runtime_error("Not implemented yet");
}

void UserRepositoryPostgres::Update(const User& user) {
    throw std::runtime_error("Not implemented yet");
}

void UserRepositoryPostgres::Delete(const User& user) {
    throw std::runtime_error("Not implemented yet");
}

std::vector<User> UserRepositoryPostgres::FindByNickname(
        const std::string& nickname) {
    throw std::runtime_error("Not implemented yet");
}


User UserRepositoryPostgres::Mapper::ToDomain(const pqxx::row& record) {
    throw std::runtime_error("Not implemented yet");
}

} // namespace music_share
