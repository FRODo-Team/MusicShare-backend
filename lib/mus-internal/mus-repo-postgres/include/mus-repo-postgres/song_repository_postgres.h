#ifndef MUS_INTERNAL_MUS_REPO_POSTGRES_SONG_REPOSITORY_POSTGRES_H_
#define MUS_INTERNAL_MUS_REPO_POSTGRES_SONG_REPOSITORY_POSTGRES_H_

#include "mus-irepo/isong_repository.h"
#include "db_connection_postgres.h"

namespace music_share {

class SongRepositoryPostgres final : public ISongRepository {
public:
    explicit SongRepositoryPostgres(const std::string& connection);
    ~SongRepositoryPostgres() = default;

    std::optional<Song> Find(uint32_t id) override;
    void Insert(Song& out_song) override;
    void Update(const Song& song) override;
    void Delete(const Song& song) override;

    std::vector<Song> FindByTitle(const std::string& title) override;
    std::vector<Song> FindByArtist(const std::string& artist) override;

private:
    class Mapper {
    public:
        static Song ToDomain(const pqxx::row& record);
    };

    DbConnectionPostgres m_database;
};

}

#endif // MUS_INTERNAL_MUS_REPO_POSTGRES_SONG_REPOSITORY_POSTGRES_H_
