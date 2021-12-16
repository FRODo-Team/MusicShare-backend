#ifndef MUS_INTERNAL_MUS_REPO_POSTGRES_PLAYLIST_REPOSITORY_POSTGRES_H_
#define MUS_INTERNAL_MUS_REPO_POSTGRES_PLAYLIST_REPOSITORY_POSTGRES_H_

#include "mus-irepo/iplaylist_repository.h"
#include "internal/repository_postgres.h"


namespace music_share {

class PlaylistRepositoryPostgres final : public IPlaylistRepository {
public:
    explicit PlaylistRepositoryPostgres(const std::string &connection_string);
    PlaylistRepositoryPostgres(const PlaylistRepositoryPostgres &) = delete;
    ~PlaylistRepositoryPostgres() = default;

    PlaylistRepositoryPostgres &operator=(const PlaylistRepositoryPostgres &) = delete;

    std::optional<Playlist> Find(uint32_t id) override;
    void Insert(Playlist &out_obj) override;
    void Update(const Playlist &obj) override;
    void Delete(const Playlist &obj) override;

    std::vector<Playlist> FindByTitle(const std::string& title) override;
    std::vector<Playlist> FindByCreatorId(uint32_t creator_id) override;
    std::vector<Playlist> FindByUserId(uint32_t user_id) override;

private:
    class SqlMapperForTablePlaylist {
    public:
        static Playlist ToDomainObject(const pqxx::row& row);
        static SqlObject ToSqlObject(const Playlist& domain);
    };

    RepositoryPostgres<Playlist, SqlMapperForTablePlaylist> m_crud_repository;
    const std::string& m_table_name;

    static constexpr std::string_view kPlaylistHasSongTableName =
            "mus_playlist_has_song";

    static constexpr std::string_view kUserHasPlaylistTableName =
            "mus_user_has_playlist";
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_REPO_POSTGRES_SONG_REPOSITORY_POSTGRES_H_
