#ifndef MUS_INTERNAL_MUS_REPO_POSTGRES_PLAYLIST_REPOSITORY_POSTGRES_H_
#define MUS_INTERNAL_MUS_REPO_POSTGRES_PLAYLIST_REPOSITORY_POSTGRES_H_

#include "mus-irepo/iplaylist_repository.h"
#include "db_connection_postgres.h"

namespace music_share {

class PlaylistRepositoryPostgres final : public IPlaylistRepository {
public:
    explicit PlaylistRepositoryPostgres(const std::string& connection);
    ~PlaylistRepositoryPostgres() = default;

    std::optional<Playlist> Find(uint32_t id) override;
    void Insert(Playlist& out_playlist) override;
    void Update(const Playlist& playlist) override;
    void Delete(const Playlist& playlist) override;

    std::vector<Playlist> FindByUserId(uint32_t user_id) override;

private:
    class Mapper {
    public:
        static Playlist ToDomain(const pqxx::row& record);
    };

    DbConnectionPostgres m_database;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_REPO_POSTGRES_SONG_REPOSITORY_POSTGRES_H_
