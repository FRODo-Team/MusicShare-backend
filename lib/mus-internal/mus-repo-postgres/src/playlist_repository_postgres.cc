#include "mus-repo-postgres/playlist_repository_postgres.h"

#include <set>
#include <algorithm>

namespace music_share {

PlaylistRepositoryPostgres::PlaylistRepositoryPostgres(
        const std::string& connection_string)
        :
        m_crud_repository(connection_string, "mus_playlist"),
        m_table_name(m_crud_repository.GetTableName()) { }

// TODO: Переписать на JOIN-ах
std::optional<Playlist> PlaylistRepositoryPostgres::Find(uint32_t id) {
    std::optional<Playlist> p = m_crud_repository.Find(id);
    if (!p) {
        return { };
    }

    std::string query =
              "SELECT song_id FROM " + std::string(kPlaylistHasSongTableName) +
             " WHERE playlist_id=" + SqlUtils::ValueToSqlFormat(id);

    pqxx::result response = m_crud_repository.ExecuteQuery(query);

    std::vector<uint32_t> song_ids;
    for (const auto& row: response) {
        auto song_id = row[0].as<uint32_t>();
        song_ids.push_back(song_id);
    }

    p->SetSongIds(song_ids);
    return p;
}

void PlaylistRepositoryPostgres::Insert(Playlist& out_obj) {
    m_crud_repository.Insert(out_obj);

    const auto& song_ids = out_obj.GetSongIds();
    const std::string playlist_id = SqlUtils::ValueToSqlFormat(out_obj.GetId().value());

    // TODO (sunz): Rewrite in single query.
    for (size_t i = 0; i < song_ids.size(); ++i) {
        std::string query =
                "INSERT INTO " + std::string(kPlaylistHasSongTableName) +
                "(playlist_id, song_id) " +
                "VALUES (" + playlist_id  + ", " +
                SqlUtils::ValueToSqlFormat(song_ids[i])  + ")";

        m_crud_repository.ExecuteQuery(query);
    }
}

void PlaylistRepositoryPostgres::Update(const Playlist& obj) {
    m_crud_repository.Update(obj);

    const auto& song_ids = obj.GetSongIds();
    const std::string playlist_id = SqlUtils::ValueToSqlFormat(obj.GetId().value());

    std::string query_songs =
            "SELECT song_id FROM " + std::string(kPlaylistHasSongTableName) + " "
            "WHERE playlist_id=" + playlist_id;

    auto response = m_crud_repository.ExecuteQuery(query_songs);
    std::set<uint32_t> stored_songs;
    for (const auto& row: response) {
        stored_songs.insert(row[0].as<uint32_t>());
    }

    std::set<uint32_t> actual_songs;
    for (uint32_t id: song_ids) {
        actual_songs.insert(id);
    }

    std::set<uint32_t> deleted_songs;
    std::set<uint32_t> inserted_songs;

    std::set_difference(
            stored_songs.begin(), stored_songs.end(),
            actual_songs.begin(), actual_songs.end(),
            std::inserter(deleted_songs, deleted_songs.end()));
    std::set_difference(
            actual_songs.begin(), actual_songs.end(),
            stored_songs.begin(), stored_songs.end(),
            std::inserter(inserted_songs, inserted_songs.end()));

    for (uint32_t song_id: inserted_songs) {
        std::string query =
                "INSERT INTO " + std::string(kPlaylistHasSongTableName) +
                "(playlist_id, song_id)" +
                "VALUES(" + playlist_id  + ", " +
                SqlUtils::ValueToSqlFormat(song_id) + ")";
        m_crud_repository.ExecuteQuery(query);
    }

    for (uint32_t song_id: deleted_songs) {
        std::string query =
                "DELETE FROM " + std::string(kPlaylistHasSongTableName) + " "
                "WHERE playlist_id=" + playlist_id + " "
                "AND song_id=" + SqlUtils::ValueToSqlFormat(song_id);
        m_crud_repository.ExecuteQuery(query);
    }
}

void PlaylistRepositoryPostgres::Delete(const Playlist& obj) {
    m_crud_repository.Delete(obj);
}

// TODO: Переписать на JOIN-ах
std::vector<Playlist> PlaylistRepositoryPostgres::FindByTitle(
        const std::string& title)
{
    std::string query =
            "SELECT id FROM " + m_table_name + " " +
            "WHERE title=" + SqlUtils::ValueToSqlFormat(title);

    pqxx::result response = m_crud_repository.ExecuteQuery(query);

    std::vector<Playlist> result;
    for (const auto& row: response) {
        assert(row[0].name() == std::string{ "id" });
        auto playlist_id = row[0].as<uint32_t>();

        std::optional<Playlist> p = Find(playlist_id);
        assert(p.has_value());
        result.push_back(p.value());
    }

    return result;
}

// TODO: Переписать на JOIN-ах
std::vector<Playlist> PlaylistRepositoryPostgres::FindByCreatorId(
        uint32_t creator_id)
{
    std::string query =
            "SELECT id FROM " + m_table_name + " " +
            "WHERE creator_id=" + SqlUtils::ValueToSqlFormat(creator_id);

    pqxx::result response = m_crud_repository.ExecuteQuery(query);

    std::vector<Playlist> result;
    for (const auto& row: response) {
        assert(row[0].name() == std::string{ "id" });
        auto id = row[0].as<uint32_t>();

        std::optional<Playlist> p = Find(id);
        assert(p.has_value());
        result.push_back(p.value());
    }

    return result;
}

// TODO: Переписать на JOIN-ах
std::vector<Playlist> PlaylistRepositoryPostgres::FindByUserId(
        uint32_t user_id)
{
    /*std::string query =
            "SELECT playlist_id FROM " + std::string(kUserHasPlaylistTableName) + " " +
            "WHERE user_id=" + SqlUtils::ValueToSqlFormat(user_id);

    pqxx::result response = m_crud_repository.ExecuteQuery(query);

    std::vector<Playlist> result;
    for (const auto& row: response) {
        assert(row[0].name() == std::string{ "playlist_id" });
        auto playlist_id = row[0].as<uint32_t>();
        std::optional<Playlist> playlist = Find(playlist_id);
        assert(playlist.has_value());
        result.push_back(*playlist);
    }*/

    std::string query = "SELECT id FROM " + m_table_name +
            " WHERE creator_id=" + SqlUtils::ValueToSqlFormat(user_id);
    pqxx::result response = m_crud_repository.ExecuteQuery(query);
    std::vector<Playlist> result;
    for (const auto& row: response) {
        assert(row[0].name() == std::string{ "id" });
        auto playlist_id = row[0].as<uint32_t>();
        std::optional<Playlist> playlist = Find(playlist_id);
        assert(playlist.has_value());
        result.push_back(*playlist);
    }

    return result;
}

Playlist PlaylistRepositoryPostgres::SqlMapperForTablePlaylist::ToDomainObject(const pqxx::row& row) {
    std::string title;
    uint32_t creator_id;
    std::optional<uint32_t> id;

    for (const auto& field: row) {
        if (field.name() == std::string{ "title" }) {
            title = field.as<std::string>();
        } else if (field.name() == std::string{ "id" }) {
            id = field.as<uint32_t>();
        } else if (field.name() == std::string{ "creator_id" }) {
            creator_id = field.as<uint32_t>();
        }
    }

    return { title, creator_id, std::vector<uint32_t>(), id };
}

SqlObject PlaylistRepositoryPostgres::SqlMapperForTablePlaylist::ToSqlObject(const Playlist& domain) {
    SqlObject o;

    o["creator_id"] = SqlUtils::ValueToSqlFormat(domain.GetCreatorId());
    o["title"] = SqlUtils::ValueToSqlFormat(domain.GetTitle());
    if(domain.GetId().has_value()) {
        o["id"] = SqlUtils::ValueToSqlFormat(domain.GetId().value());
    }

    return o;
}

} // namespace music_share
