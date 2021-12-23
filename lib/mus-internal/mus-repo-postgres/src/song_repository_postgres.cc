// Owners: Rostislav Vivcharuk, WEB-12
#include "mus-repo-postgres/song_repository_postgres.h"

namespace music_share {

SongRepositoryPostgres::SongRepositoryPostgres(
        const std::string& connection_string)
        :
        m_crud_repository(connection_string, "mus_song"),
        m_table_name(m_crud_repository.GetTableName()) { }

std::optional<Song> SongRepositoryPostgres::Find(uint32_t id) { 
    return m_crud_repository.Find(id);
}

void SongRepositoryPostgres::Insert(Song& out_song) { 
    return m_crud_repository.Insert(out_song);
}

void SongRepositoryPostgres::Update(const Song& song) {
    return m_crud_repository.Update(song);
}

void SongRepositoryPostgres::Delete(const Song& song) {
    return m_crud_repository.Delete(song);
}

std::vector<Song> SongRepositoryPostgres::FetchAll(
        std::optional<uint32_t> limit)
{
    std::string query = "SELECT * FROM " + m_table_name + " ";
    if (limit.has_value()) {
        query += " LIMIT " + SqlUtils::ValueToSqlFormat(limit.value());
    }

    pqxx::result response = m_crud_repository.ExecuteQuery(query);

    std::vector<Song> result;
    for (const auto& row: response) {
        Song s = SqlMapper::ToDomainObject(row);
        result.push_back(s);
    }

    return result;
}

std::vector<Song> SongRepositoryPostgres::FindByTitle(
        const std::string& title)
{
    std::string query =
            "SELECT * FROM " + m_table_name + " " +
            "WHERE title=" + SqlUtils::ValueToSqlFormat(title);

    pqxx::result response = m_crud_repository.ExecuteQuery(query);

    std::vector<Song> result;
    for (const auto& row: response) {
        Song s = SqlMapper::ToDomainObject(row);
        result.push_back(s);
    }

    return result;
}

std::vector<Song> SongRepositoryPostgres::FindByArtist(
        const std::string& artist)
{
    std::string query =
            "SELECT * FROM " + m_table_name + " " +
            "WHERE artist=" + SqlUtils::ValueToSqlFormat(artist);

    pqxx::result response = m_crud_repository.ExecuteQuery(query);

    std::vector<Song> result;
    for (const auto& row: response) {
        Song s = SqlMapper::ToDomainObject(row);
        result.push_back(s);
    }

    return result;
}


Song SongRepositoryPostgres::SqlMapper::ToDomainObject(const pqxx::row& row) {
    std::string title;
    std::string artist;
    std::string duration;
    std::string url;
    std::optional<uint32_t> year;
    std::optional<std::string> album;
    std::optional<std::string> genre;
    std::optional<uint32_t> id;

    for (const auto& field: row) {
        if (field.name() == std::string{ "title" }) {
            title = field.as<std::string>();
        } else if (field.name() == std::string{ "artist" }) {
            artist = field.as<std::string>();
        } else if (field.name() == std::string{ "duration" }) {
            duration = field.as<std::string>();
        } else if (field.name() == std::string{ "url" }) {
            url = field.as<std::string>();
        } else if (field.name() == std::string{ "year" }) {
            year = field.as<uint32_t>();
        } else if (field.name() == std::string{ "album" }) {
            album = field.as<std::string>();
        } else if (field.name() == std::string{ "genre" }) {
            genre = field.as<std::string>();
        } else if (field.name() == std::string{ "id" }) {
            id = field.as<uint32_t>();
        }
    }

    return { title, artist, duration, url, year, album, genre, id };
}

SqlObject SongRepositoryPostgres::SqlMapper::ToSqlObject(const Song& domain) {
    SqlObject result;

    result["title"] = SqlUtils::ValueToSqlFormat(domain.GetTitle());
    result["artist"] = SqlUtils::ValueToSqlFormat(domain.GetArtist());
    result["duration"] = SqlUtils::ValueToSqlFormat(domain.GetDuration());
    result["url"] = SqlUtils::ValueToSqlFormat(domain.GetUrl());


    if (domain.GetYear().has_value()) {
        result["year"] = SqlUtils::ValueToSqlFormat(domain.GetYear().value());
    }
    if (domain.GetAlbum().has_value()) {
        result["album"] = SqlUtils::ValueToSqlFormat(domain.GetAlbum().value());
    }
    if (domain.GetGenre().has_value()) {
        result["genre"] = SqlUtils::ValueToSqlFormat(domain.GetGenre().value());
    }
    if (domain.GetId().has_value()) {
        result["id"] = SqlUtils::ValueToSqlFormat(domain.GetId().value());
    }

    return result;
}

} // namespace music_share