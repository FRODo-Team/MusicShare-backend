// Owners: Rostislav Vivcharuk, WEB-12
#ifndef MUS_INTERNAL_MUS_REPO_POSTGRES_SONG_REPOSITORY_POSTGRES_H_
#define MUS_INTERNAL_MUS_REPO_POSTGRES_SONG_REPOSITORY_POSTGRES_H_

#include "mus-irepo/isong_repository.h"
#include "mus-repo-postgres/internal/repository_postgres.h"


namespace music_share {

class SongRepositoryPostgres final : public ISongRepository {
public:
    explicit SongRepositoryPostgres(const std::string& connection_string);
    SongRepositoryPostgres(const SongRepositoryPostgres&) = delete;
    ~SongRepositoryPostgres() = default;

    SongRepositoryPostgres& operator=(const SongRepositoryPostgres&) = delete;

    std::optional<Song> Find(uint32_t id) override;
    void Insert(Song& out_obj) override;
    void Update(const Song& obj) override;
    void Delete(const Song& obj) override;

    std::vector<Song> FetchAll(std::optional<uint32_t> limit = { }) override;
    std::vector<Song> FindByTitle(const std::string& title) override;
    std::vector<Song> FindByArtist(const std::string& artist) override;

private:
    class SqlMapper {
    public:
        static Song ToDomainObject(const pqxx::row& row);
        static SqlObject ToSqlObject(const Song& domain);
    };

    RepositoryPostgres<Song, SqlMapper> m_crud_repository;
    const std::string& m_table_name;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_REPO_POSTGRES_SONG_REPOSITORY_POSTGRES_H_
