#include "mus-repo-postgres/playlist_repository_postgres.h"

namespace music_share {

PlaylistRepositoryPostgres::PlaylistRepositoryPostgres(
        const std::string& connection)
        : m_database(connection) {
    throw std::runtime_error("Not implemented yet");
}

std::optional<Playlist> PlaylistRepositoryPostgres::Find(uint32_t id) {
    throw std::runtime_error("Not implemented yet");
}

void PlaylistRepositoryPostgres::Insert(Playlist& out_playlist) {
    throw std::runtime_error("Not implemented yet");
}

void PlaylistRepositoryPostgres::Update(const Playlist& playlist) {
    throw std::runtime_error("Not implemented yet");
}

void PlaylistRepositoryPostgres::Delete(const Playlist& playlist) {
    throw std::runtime_error("Not implemented yet");
}

std::vector<Playlist> PlaylistRepositoryPostgres::FindByUserId(
        uint32_t user_id) {
    throw std::runtime_error("Not implemented yet");
}


Playlist PlaylistRepositoryPostgres::Mapper::ToDomain(const pqxx::row& record) {
    throw std::runtime_error("Not implemented yet");
}

} // namespace music_share
