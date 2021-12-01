#include <gtest/gtest.h>
#include <memory>

#include "mus-repo-postgres/song_repository_postgres.h"

using music_share::SongRepositoryPostgres;
using music_share::Song;

/*
    Данный тест имеет смысл при наличии поднятой тестовой базы данных.
    TODO: Определить наполнение тестовой БД,
          Дописать FindByTitle, FindByArtist.
 */

class TestSongRepositoryPostgres : public ::testing::Test {
protected:
    static const std::string s_ConnectionString;
};

const std::string TestSongRepositoryPostgres::s_ConnectionString = "connection to test database";


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
        EXPECT_STREQ(expected_song.GetTitle().c_str(), actual_song->GetTitle().c_str());
        EXPECT_STREQ(expected_song.GetArtist().c_str(), actual_song->GetArtist().c_str());
        EXPECT_STREQ(expected_song.GetDuration().c_str(), actual_song->GetDuration().c_str());
        EXPECT_STREQ(expected_song.GetUrl().c_str(), actual_song->GetUrl().c_str());
        EXPECT_EQ(expected_song.GetYear(), actual_song->GetYear());
        EXPECT_STREQ(expected_song.GetAlbum()->c_str(), actual_song->GetAlbum()->c_str());
        EXPECT_STREQ(expected_song.GetGenre()->c_str(), actual_song->GetGenre()->c_str());
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

TEST_F(TestSongRepositoryPostgres, Insert) {
    // arrange
    const uint32_t id = 2;
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
    EXPECT_STREQ(expected_song.GetTitle().c_str(), song_to_insert.GetTitle().c_str());
    EXPECT_STREQ(expected_song.GetArtist().c_str(), song_to_insert.GetArtist().c_str());
    EXPECT_STREQ(expected_song.GetDuration().c_str(), song_to_insert.GetDuration().c_str());
    EXPECT_STREQ(expected_song.GetUrl().c_str(), song_to_insert.GetUrl().c_str());
    EXPECT_EQ(expected_song.GetYear(), song_to_insert.GetYear());
    EXPECT_STREQ(expected_song.GetAlbum()->c_str(), song_to_insert.GetAlbum()->c_str());
    EXPECT_STREQ(expected_song.GetGenre()->c_str(), song_to_insert.GetGenre()->c_str());
    EXPECT_EQ(expected_song.GetId(), song_to_insert.GetId());
}

TEST_F(TestSongRepositoryPostgres, Update) {
    // arrange
    const uint32_t id = 2;

    Song song_to_update("UPDATED_TITLE", "lildude", "14.88",
                        "/trash/UPDATED_NAME.mp4", 1917, "unknown", "RAP", id);

    // act
    auto repo = std::make_unique<SongRepositoryPostgres>(s_ConnectionString);
    repo->Update(song_to_update);

    // assert
    std::optional<Song> song_updated = repo->Find(id);
    EXPECT_TRUE(song_updated.has_value());
    if (song_updated) {
        EXPECT_STREQ(song_updated->GetTitle().c_str(), song_to_update.GetTitle().c_str());
        EXPECT_STREQ(song_updated->GetArtist().c_str(), song_to_update.GetArtist().c_str());
        EXPECT_STREQ(song_updated->GetDuration().c_str(), song_to_update.GetDuration().c_str());
        EXPECT_STREQ(song_updated->GetUrl().c_str(), song_to_update.GetUrl().c_str());
        EXPECT_EQ(song_updated->GetYear(), song_to_update.GetYear());
        EXPECT_STREQ(song_updated->GetAlbum()->c_str(), song_to_update.GetAlbum()->c_str());
        EXPECT_STREQ(song_updated->GetGenre()->c_str(), song_to_update.GetGenre()->c_str());
        EXPECT_EQ(song_updated->GetId(), song_to_update.GetId());
    }
}


TEST_F(TestSongRepositoryPostgres, Delete) {
    // arrange
    const uint32_t id = 2;
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
    // arrange
    // act
    auto repo = std::make_unique<SongRepositoryPostgres>(s_ConnectionString);
    std::vector<Song> songs = repo->FindByTitle("title");
    // assert
}

TEST_F(TestSongRepositoryPostgres, FindByArtist) {
    // arrange
    // act
    auto repo = std::make_unique<SongRepositoryPostgres>(s_ConnectionString);
    std::vector<Song> songs = repo->FindByArtist("dude");
    // assert
}
