#include "mus-repo-postgres/song_repository_postgres.h"

namespace music_share {

SongRepositoryPostgres::SongRepositoryPostgres(
        std::unique_ptr<DbConnectionPostgres> db)
        : m_database(std::move(db)) {
    throw std::runtime_error("Not implemented yet");
}

std::optional<Song> SongRepositoryPostgres::Find(uint32_t id) { 
    throw std::runtime_error("Not implemented yet");
}

void SongRepositoryPostgres::Insert(Song& out_song) { 
    throw std::runtime_error("Not implemented yet");
}

void SongRepositoryPostgres::Update(const Song& song) {
    throw std::runtime_error("Not implemented yet");
}

void SongRepositoryPostgres::Delete(const Song& song) {
    throw std::runtime_error("Not implemented yet");
}

std::vector<Song> SongRepositoryPostgres::FindByTitle(
    const std::string& title) {
    throw std::runtime_error("Not implemented yet");
}

std::vector<Song> SongRepositoryPostgres::FindByArtist(
    const std::string& artist) {
    throw std::runtime_error("Not implemented yet");
}

} // namespace music_share
