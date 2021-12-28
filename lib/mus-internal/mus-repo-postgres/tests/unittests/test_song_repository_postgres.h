// Owners: Rostislav Vivcharuk, WEB-12
#include <gtest/gtest.h>
#include <memory>
#include <fstream>
#include <sstream>

#include "mus-repo-postgres/song_repository_postgres.h"

using music_share::SongRepositoryPostgres;
using music_share::Song;
using music_share::DatabaseObject;

class TestSongRepositoryPostgres : public ::testing::Test {
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
    }

    static void TearDownTestSuite() {
        DatabaseObject dbo(s_ConnectionString);
        for (const auto& filepath: s_TestDatabaseDeinitSqlScripts) {
            std::ifstream file(filepath);
            if (!file.is_open()) {
                throw std::runtime_error("Failed to read test database teardown script");
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

const std::string TestSongRepositoryPostgres::s_ConnectionString =
        DatabaseObject::MakeConnectionString("localhost", 5432, "sunz", "123123123", "mus_test_song");

// TODO: Написать конфиг файл для такого рода вещей
const std::vector<std::string> TestSongRepositoryPostgres::s_TestDatabaseInitSqlScripts = {
        std::string{ "/home/sunz/uni/parkmail-cpp/MusicShare-backend/db/postgres/migrations/v0001_021221_MUS-28_create_tables.sql" }
};

// TODO: Написать конфиг файл для такого рода вещей
const std::vector<std::string> TestSongRepositoryPostgres::s_TestDatabaseDeinitSqlScripts = {
    std::string{ "/home/sunz/uni/parkmail-cpp/MusicShare-backend/db/postgres/migrations/u0001_021221_MUS-28_create_tables.sql" }
};


TEST_F(TestSongRepositoryPostgres, Insert) {
    // arrange
    const uint32_t id = 1;
    Song song_to_insert("somestupidmodernsongname", "lildude", "14.88",
                        "/trash/nonsense.mp4", 1917, "unknown", "hip-hop",
                        std::nullopt);

    Song expected_song("somestupidmodernsongname", "lildude", "14.88",
                       "/trash/nonsense.mp4", 1917, "unknown", "hip-hop",
                       id);

    // act
    auto repo = std::make_unique<SongRepositoryPostgres>(s_ConnectionString);
    repo->Insert(song_to_insert);

    // assert
    EXPECT_STREQ(expected_song.GetTitle().c_str(),
                 song_to_insert.GetTitle().c_str());

    EXPECT_STREQ(expected_song.GetArtist().c_str(),
                 song_to_insert.GetArtist().c_str());

    EXPECT_STREQ(expected_song.GetDuration().c_str(),
                 song_to_insert.GetDuration().c_str());

    EXPECT_STREQ(expected_song.GetUrl().c_str(),
                 song_to_insert.GetUrl().c_str());

    EXPECT_EQ(expected_song.GetYear(),
              song_to_insert.GetYear());

    EXPECT_STREQ(expected_song.GetAlbum()->c_str(),
                 song_to_insert.GetAlbum()->c_str());

    EXPECT_STREQ(expected_song.GetGenre()->c_str(),
                 song_to_insert.GetGenre()->c_str());

    EXPECT_EQ(expected_song.GetId(), song_to_insert.GetId());
}

TEST_F(TestSongRepositoryPostgres, Find) {
    // arrange
    const uint32_t id = 1;
    Song expected_song("somestupidmodernsongname", "lildude", "14.88",
                       "/trash/nonsense.mp4", 1917, "unknown", "hip-hop", id);

    // act
    auto repo = std::make_unique<SongRepositoryPostgres>(s_ConnectionString);
    std::optional<Song> actual_song = repo->Find(id);

    // assert
    EXPECT_TRUE(actual_song.has_value());
    if (actual_song) {
        EXPECT_STREQ(expected_song.GetTitle().c_str(),
                     actual_song->GetTitle().c_str());

        EXPECT_STREQ(expected_song.GetArtist().c_str(),
                     actual_song->GetArtist().c_str());

        EXPECT_STREQ(expected_song.GetDuration().c_str(),
                     actual_song->GetDuration().c_str());

        EXPECT_STREQ(expected_song.GetUrl().c_str(),
                     actual_song->GetUrl().c_str());

        EXPECT_EQ(expected_song.GetYear(),
                  actual_song->GetYear());

        EXPECT_STREQ(expected_song.GetAlbum()->c_str(),
                     actual_song->GetAlbum()->c_str());

        EXPECT_STREQ(expected_song.GetGenre()->c_str(),
                     actual_song->GetGenre()->c_str());

        EXPECT_EQ(expected_song.GetId(), actual_song->GetId());
    }
}

TEST_F(TestSongRepositoryPostgres, FindNotExistingSong) {
    // arrange
    const uint32_t song_id_to_find = 1123123123;

    // act
    auto repo = std::make_unique<SongRepositoryPostgres>(s_ConnectionString);
    std::optional<Song> actual_song = repo->Find(song_id_to_find);

    // assert
    EXPECT_FALSE(actual_song.has_value());
}

TEST_F(TestSongRepositoryPostgres, Update) {
    // arrange
    const uint32_t id = 1;

    Song song_to_update("UPDATED_TITLE", "lildude", "14.88",
                        "/trash/UPDATED_NAME.mp4", 1917, "unknown", "RAP", id);

    // act
    auto repo = std::make_unique<SongRepositoryPostgres>(s_ConnectionString);
    repo->Update(song_to_update);

    // assert
    std::optional<Song> song_updated = repo->Find(id);
    EXPECT_TRUE(song_updated.has_value());
    if (song_updated) {
        EXPECT_STREQ(song_updated->GetTitle().c_str(),
                     song_to_update.GetTitle().c_str());

        EXPECT_STREQ(song_updated->GetArtist().c_str(),
                     song_to_update.GetArtist().c_str());

        EXPECT_STREQ(song_updated->GetDuration().c_str(),
                     song_to_update.GetDuration().c_str());

        EXPECT_STREQ(song_updated->GetUrl().c_str(),
                     song_to_update.GetUrl().c_str());

        EXPECT_EQ(song_updated->GetYear(), song_to_update.GetYear());

        EXPECT_STREQ(song_updated->GetAlbum()->c_str(),
                     song_to_update.GetAlbum()->c_str());

        EXPECT_STREQ(song_updated->GetGenre()->c_str(),
                     song_to_update.GetGenre()->c_str());

        EXPECT_EQ(song_updated->GetId(), song_to_update.GetId());
    }
}

TEST_F(TestSongRepositoryPostgres, Delete) {
    // arrange
    const uint32_t id = 1;
    const Song song_to_delete("UPDATED_NAME", "lildude", "14.88",
                              "/trash/nonsense.mp4", 1917, "unknown", "hip-hop",
                              id);

    // act
    auto repo = std::make_unique<SongRepositoryPostgres>(s_ConnectionString);
    repo->Delete(song_to_delete);

    // assert
    std::optional<Song> song_updated = repo->Find(id);
    EXPECT_FALSE(song_updated.has_value());
}

TEST_F(TestSongRepositoryPostgres, FindByTitle) {
    // TODO(sunz): move somewhere to fixture
    DatabaseObject db(s_ConnectionString);
    db.ExecuteQuery(
        "INSERT INTO mus_song(title, artist, duration, url, year, album, genre) "
        "VALUES "
                "('Better Off Alone', 'Alice Deejay', '2.56', 'https://www.youtube.com/watch?v=Lgs9QUtWc3M', 1998, 'Unknown', 'trance'), "
                "('Better Off Alone', 'Alice Deejay', '2.56', '/somepath', 1998, 'Unknown', 'Unknown'), "
                "('Smooth Criminal', 'Alient Ant Farm', '3.33', '/music/nostalgic', 2001, 'Unknown', 'Punk')");

    // arrange
    const std::string title_to_find = "Better Off Alone";
    std::vector<Song> expected_songs = {
            Song(
                "Better Off Alone",
                "Alice Deejay",
                "2.56",
                "https://www.youtube.com/watch?v=Lgs9QUtWc3M",
                1998,
                "Unknown",
                "trance"),

            Song("Better Off Alone",
                 "Alice Deejay",
                 "2.56",
                 "/somepath",
                 1998,
                 "Unknown",
                 "Unknown")
    };

    // act
    auto repo = std::make_unique<SongRepositoryPostgres>(s_ConnectionString);
    std::vector<Song> actual_songs = repo->FindByTitle("Better Off Alone");

    // assert
    ASSERT_EQ(expected_songs.size(), actual_songs.size());
    for (size_t i = 0; i < actual_songs.size(); ++i) {
        const auto& expected_song = expected_songs[i];
        const auto& actual_song = actual_songs[i];

        EXPECT_STREQ(actual_song.GetTitle().c_str(),
                     expected_song.GetTitle().c_str());

        EXPECT_STREQ(actual_song.GetArtist().c_str(),
                     expected_song.GetArtist().c_str());

        EXPECT_STREQ(actual_song.GetDuration().c_str(),
                     expected_song.GetDuration().c_str());

        EXPECT_STREQ(actual_song.GetUrl().c_str(),
                     expected_song.GetUrl().c_str());

        EXPECT_EQ(actual_song.GetYear(), expected_song.GetYear());

        EXPECT_STREQ(actual_song.GetAlbum()->c_str(),
                     expected_song.GetAlbum()->c_str());

        EXPECT_STREQ(actual_song.GetGenre()->c_str(),
                     expected_song.GetGenre()->c_str());
    }
}

TEST_F(TestSongRepositoryPostgres, FindByArtist) {
    // arrange
    std::vector<Song> expected_songs = {
            Song("Better Off Alone",
                 "Alice Deejay",
                 "2.56",
                 "https://www.youtube.com/watch?v=Lgs9QUtWc3M",
                 1998,
                 "Unknown",
                 "trance"),

            Song("Better Off Alone",
                 "Alice Deejay",
                 "2.56",
                 "/somepath",
                 1998,
                 "Unknown",
                 "Unknown")
    };

    // act
    auto repo = std::make_unique<SongRepositoryPostgres>(s_ConnectionString);
    std::vector<Song> actual_songs = repo->FindByArtist("Alice Deejay");

    // assert
    ASSERT_EQ(expected_songs.size(), actual_songs.size());
    for (size_t i = 0; i < actual_songs.size(); ++i) {
        const auto& expected_song = expected_songs[i];
        const auto& actual_song = actual_songs[i];

        EXPECT_STREQ(actual_song.GetTitle().c_str(),
                     expected_song.GetTitle().c_str());

        EXPECT_STREQ(actual_song.GetArtist().c_str(),
                     expected_song.GetArtist().c_str());

        EXPECT_STREQ(actual_song.GetDuration().c_str(),
                     expected_song.GetDuration().c_str());

        EXPECT_STREQ(actual_song.GetUrl().c_str(),
                     expected_song.GetUrl().c_str());

        EXPECT_EQ(actual_song.GetYear(), expected_song.GetYear());

        EXPECT_STREQ(actual_song.GetAlbum()->c_str(),
                     expected_song.GetAlbum()->c_str());

        EXPECT_STREQ(actual_song.GetGenre()->c_str(),
                     expected_song.GetGenre()->c_str());
    }
}

TEST_F(TestSongRepositoryPostgres, FetchAllNoLimit) {
    // arrange
    const size_t expectedSongCount = 3;

    // act
    auto repo = std::make_unique<SongRepositoryPostgres>(s_ConnectionString);
    std::vector<Song> actual_songs = repo->FetchAll();

    ASSERT_EQ(actual_songs.size(), expectedSongCount);
}
