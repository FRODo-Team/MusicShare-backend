#include <gtest/gtest.h>
#include <memory>

#include "mus-repo-postgres/playlist_repository_postgres.h"

using music_share::PlaylistRepositoryPostgres;
using music_share::Playlist;

/*
    Данный тест имеет смысл при наличии поднятой тестовой базы данных.
    TODO: Определить наполнение тестовой БД,
          Дописать
 */

class TestPlaylistRepositoryPostgres : public ::testing::Test {
protected:
    static const std::string s_ConnectionString;
};

const std::string TestPlaylistRepositoryPostgres::s_ConnectionString = "connection to test database";


TEST_F(TestPlaylistRepositoryPostgres, Find) {
    // arrange
    const uint32_t id = 1;
    Playlist expected_playlist(1, "MyPlaylist", std::vector<uint32_t>({1,2,3,4,5}), id);

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

TEST_F(TestPlaylistRepositoryPostgres, Insert) {
    // arrange
    const uint32_t expected_id = 2;
    Playlist playlist_to_insert(1, "MyPlaylist", std::vector<uint32_t>({1,2}));
    Playlist expected_playlist(1, "MyPlaylist", std::vector<uint32_t>({1,2}), expected_id);

    // act
    auto repo = std::make_unique<PlaylistRepositoryPostgres>(s_ConnectionString);
    repo->Insert(playlist_to_insert);

    // assert
    EXPECT_EQ(playlist_to_insert.GetId(), expected_playlist.GetId());
    EXPECT_STREQ(playlist_to_insert.GetTitle().c_str(), expected_playlist.GetTitle().c_str());
    EXPECT_EQ(playlist_to_insert.GetCreatorId(), expected_playlist.GetCreatorId());
    EXPECT_TRUE(playlist_to_insert.GetSongIds() == expected_playlist.GetSongIds());
}

TEST_F(TestPlaylistRepositoryPostgres, Update) {
    // arrange
    const uint32_t id = 2;
    const Playlist playlist_to_update(1, "MyPlaylistUPDATED", std::vector<uint32_t>({1,2,3}));

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
    const uint32_t id = 2;
    const Playlist playlist_to_delete(1, "MyPlaylistUPDATED", std::vector<uint32_t>({1,2,3}));

    // act
    auto repo = std::make_unique<PlaylistRepositoryPostgres>(s_ConnectionString);
    repo->Delete(playlist_to_delete);

    // assert
    std::optional<Playlist> playlist_deleted = repo->Find(id);
    EXPECT_FALSE(playlist_deleted.has_value());
}

TEST_F(TestPlaylistRepositoryPostgres, FindByUserId) {
    // arrange
    const uint32_t user_id = 2;

    // act
    auto repo = std::make_unique<PlaylistRepositoryPostgres>(s_ConnectionString);
    std::vector<Playlist> playlists = repo->FindByUserId(user_id);

    // assert
    EXPECT_TRUE(playlists.size() > 0);
    if (playlists.size() > 0) {
        // TODO
    }
}
