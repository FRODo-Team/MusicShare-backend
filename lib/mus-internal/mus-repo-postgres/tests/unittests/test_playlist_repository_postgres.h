#include <gtest/gtest.h>
#include <memory>
#include <fstream>
#include <sstream>

#include "mus-repo-postgres/playlist_repository_postgres.h"

using music_share::PlaylistRepositoryPostgres;
using music_share::Playlist;
using music_share::DatabaseObject;

//      !   Добавить тест для FindByUserId          !

class TestPlaylistRepositoryPostgres : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        DatabaseObject dbo(s_ConnectionString);
        for (const auto& filepath: s_TestDatabaseInitSqlScripts) {
            std::ifstream file(filepath);
            if (!file.is_open()) {
                throw std::runtime_error("Failed to read test database setup script");
            }
            std::stringstream buffer;
            buffer << file.rdbuf();
            std::string query = buffer.str();
            dbo.ExecuteQuery(query);
        }

        dbo.ExecuteQuery(
                "INSERT INTO mus_user(username, email, password_hash, nickname, access_level)"
                "VALUES ('username2', 'mail2@mail.ru', '321', 'nickname2', 1)");
        dbo.ExecuteQuery(
                "INSERT INTO mus_song(title, artist, duration, url, year, album, genre) "
                "VALUES"
                "('Better Off Alone', 'Alice Deejay', '2.56', 'https://www.youtube.com/watch?v=Lgs9QUtWc3M', 1998, 'Unknown', 'trance'), "
                "('Better Off Alone Remix', 'DJ Cocos', '2.56', '/blahblah', 1998, 'Unknown', 'Unknown')");
    }

    static void TearDownTestSuite() {
        DatabaseObject dbo(s_ConnectionString);
        for (const auto& filepath: s_TestDatabaseDeinitSqlScripts) {
            std::ifstream file(filepath);
            if (!file.is_open()) {
                throw std::runtime_error("Failed to read test teardown setup script");
            }
            std::stringstream buffer;
            buffer << file.rdbuf();
            std::string query = buffer.str();
            dbo.ExecuteQuery(query);
        }
    }

protected:
    static const std::string s_ConnectionString;
    static const std::vector<std::string> s_TestDatabaseInitSqlScripts;
    static const std::vector<std::string> s_TestDatabaseDeinitSqlScripts;
};

const std::string TestPlaylistRepositoryPostgres::s_ConnectionString =
        DatabaseObject::MakeConnectionString("localhost", 5432, "sunz", "123123123", "mus_test_playlist");

// TODO: Написать конфиг файл для такого рода вещей
const std::vector<std::string> TestPlaylistRepositoryPostgres::s_TestDatabaseInitSqlScripts = {
        std::string{ "/home/sunz/uni/parkmail-cpp/MusicShare-backend/db/postgres/migrations/v0001_021221_MUS-28_create_tables.sql" }
};

// TODO: Написать конфиг файл для такого рода вещей
const std::vector<std::string> TestPlaylistRepositoryPostgres::s_TestDatabaseDeinitSqlScripts = {
        std::string{ "/home/sunz/uni/parkmail-cpp/MusicShare-backend/db/postgres/migrations/u0001_021221_MUS-28_create_tables.sql" }
};


TEST_F(TestPlaylistRepositoryPostgres, Insert) {
    // arrange
    const uint32_t expected_id = 1;
    Playlist playlist_to_insert("90s Hits", 1, std::vector<uint32_t>({1,2}));
    Playlist expected_playlist("90s Hits", 1, std::vector<uint32_t>({1,2}), expected_id);

    // act
    auto repo = std::make_unique<PlaylistRepositoryPostgres>(s_ConnectionString);
    repo->Insert(playlist_to_insert);

    // assert
    EXPECT_EQ(playlist_to_insert.GetId(), expected_playlist.GetId());
    EXPECT_STREQ(playlist_to_insert.GetTitle().c_str(), expected_playlist.GetTitle().c_str());
    EXPECT_EQ(playlist_to_insert.GetCreatorId(), expected_playlist.GetCreatorId());
    EXPECT_TRUE(playlist_to_insert.GetSongIds() == expected_playlist.GetSongIds());
}

TEST_F(TestPlaylistRepositoryPostgres, Find) {
    // arrange
    const uint32_t id = 1;
    Playlist expected_playlist("90s Hits", 1, std::vector<uint32_t>({1,2}), id);

    // act
    auto repo = std::make_unique<PlaylistRepositoryPostgres>(s_ConnectionString);
    std::optional<Playlist> actual_playlist = repo->Find(id);

    // assert
    EXPECT_TRUE(actual_playlist.has_value());
    if (actual_playlist) {
        EXPECT_STREQ(expected_playlist.GetTitle().c_str(), actual_playlist->GetTitle().c_str());
        EXPECT_TRUE(expected_playlist.GetSongIds() == actual_playlist->GetSongIds());
        EXPECT_EQ(expected_playlist.GetCreatorId(), actual_playlist->GetCreatorId());
        EXPECT_EQ(expected_playlist.GetId(), actual_playlist->GetId());
    }
}

TEST_F(TestPlaylistRepositoryPostgres, FindNotExistingPlaylist) {
    // arrange
    const uint32_t id = 2;

    // act
    auto repo = std::make_unique<PlaylistRepositoryPostgres>(s_ConnectionString);
    std::optional<Playlist> actual_playlist = repo->Find(id);

    // assert
    EXPECT_FALSE(actual_playlist.has_value());
}

TEST_F(TestPlaylistRepositoryPostgres, Update) {
    // arrange
    const uint32_t id = 1;
    const Playlist playlist_to_update("90s HitsUPDATED", 1, std::vector<uint32_t>({1,2}), id);

    // act
    auto repo = std::make_unique<PlaylistRepositoryPostgres>(s_ConnectionString);
    repo->Update(playlist_to_update);

    // assert
    std::optional<Playlist> playlist_updated = repo->Find(id);
    EXPECT_TRUE(playlist_updated.has_value());
    if (playlist_updated) {
        EXPECT_STREQ(playlist_to_update.GetTitle().c_str(), playlist_updated->GetTitle().c_str());
        EXPECT_TRUE(playlist_to_update.GetSongIds() == playlist_updated->GetSongIds());
        EXPECT_EQ(playlist_to_update.GetCreatorId(), playlist_updated->GetCreatorId());
        EXPECT_EQ(playlist_to_update.GetId(), playlist_updated->GetId());
    }
}

TEST_F(TestPlaylistRepositoryPostgres, Delete) {
    // arrange
    const Playlist playlist_to_delete("90s HitsUPDATED", 1, std::vector<uint32_t>({1,2}), 1);

    // act
    auto repo = std::make_unique<PlaylistRepositoryPostgres>(s_ConnectionString);
    repo->Delete(playlist_to_delete);

    // assert
    std::optional<Playlist> playlist_deleted = repo->Find(1);
    EXPECT_FALSE(playlist_deleted.has_value());
}
