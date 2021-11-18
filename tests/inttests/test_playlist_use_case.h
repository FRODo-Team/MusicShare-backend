#ifndef TESTS_INTTESTS_TEST_PLAYLIST_USE_CASE_H_
#define TESTS_INTTESTS_TEST_PLAYLIST_USE_CASE_H_

#include "gtest/gtest.h"

#include <memory>
#include <cstdint>
#include <vector>

#include "mus-irepo/iplaylist_repository.h"
#include "mus-usecase/playlist_use_case.h"
#include "mus-dto/playlist_response_dto.h"

using std::vector;
using std::string;
using std::shared_ptr;
using std::make_shared;
using music_share::IPlaylistRepository;
using std::optional;
using std::nullopt;
using music_share::PlaylistUseCase;

class TestPlaylistUseCase : public ::testing::Test {
protected:
    void SetUp() {
        shared_ptr<IPlaylistRepository> song_rep = make_shared<PlaylistRepositoryPostgres>(connection_to_database);
        m_playlist_use_case = make_shared<PlaylistUseCase>(*song_rep);
        std::vector<uint32_t> song_ids(1, 1);
        m_playlist_request = make_shared<PlaylistRequestDTO>("Window", song_ids);
        m_id = m_playlist_use_case->Create(1, *m_playlist_request);
    }
    void TearDown() { }

    shared_ptr<IPlaylistUseCase> m_playlist_use_case;
    shared_ptr<PlaylistRequestDTO> m_playlist_request;
    optional<uint32_t> m_id;
};

TEST_F(TestPlaylistUseCase, Create) {
    std::vector<uint32_t> song_ids(1, 2);
    PlaylistRequestDTO playlist_request("Sun", song_ids);

    optional<uint32_t> id = m_playlist_use_case->Create(1, playlist_request);
    optional<PlaylistResponseDTO> playlist_response = nullopt;

    if (id) {
        playlist_response = m_playlist_use_case->GetById(*id);
    }
    if (playlist_response) {
        EXPECT_EQ(playlist_response->songs_count, 1);
        EXPECT_EQ(playlist_response->title, "Sun");
    }
}

TEST_F(TestPlaylistUseCase, DeleteById) {
    if (m_id) {
        EXPECT_TRUE(m_playlist_use_case->DeleteById(1, *m_id));
    }

    optional<PlaylistResponseDTO> playlist_response = m_playlist_use_case->GetById(*m_id);
    EXPECT_EQ(playlist_response, nullopt);
}

TEST_F(TestPlaylistUseCase, AddSongById) {
    std::vector<uint32_t> song_ids(1, 2);
    PlaylistSongRequestDTO song(song_ids);

    if (m_id) {
        EXPECT_TRUE(m_playlist_use_case->AddSongById(song, *m_id, 1));
    }

    optional<PlaylistResponseDTO> playlist_response = nullopt;
    if (m_id) {
        playlist_response = m_playlist_use_case->GetById(*m_id);
    }
    if (playlist_response) {
        EXPECT_EQ(playlist_response->songs_count, 2);
    }
}

TEST_F(TestPlaylistUseCase, DeleteSongById) {
    std::vector<uint32_t> song_ids(1, 2);
    PlaylistSongRequestDTO song(song_ids);
    bool result = false;
    if (m_id) {
        result = m_playlist_use_case->AddSongById(song, *m_id, 1);
    }

    if (result) {
        EXPECT_TRUE(m_playlist_use_case->DeleteSongById(2, *m_id, 1));
    }
}

TEST_F(TestPlaylistUseCase, GetByUserId) {
    vector<PlaylistResponseDTO> playlist;

    if (m_id) {
        playlist = m_playlist_use_case->GetByUserId(1, 1);
    }

    EXPECT_EQ(playlist[0].songs_count, 1);
    EXPECT_EQ(playlist[0].id, *m_id);
    EXPECT_EQ(playlist[0].author_id, 1);
}

TEST_F(TestPlaylistUseCase, GetById) {
    std::optional<PlaylistResponseDTO> playlist = nullopt;

    if (m_id) {
        playlist = m_playlist_use_case->GetById(*m_id);
    }

    if (playlist) {
        EXPECT_EQ(playlist->songs_count, 1);
        EXPECT_EQ(playlist->id, *m_id);
        EXPECT_EQ(playlist->author_id, 1);
    }
}

TEST_F(TestPlaylistUseCase, GetSongs) {
    std::vector<SongResponseDTO> songs;

    if (m_id) {
        songs = m_playlist_use_case->GetSongs(*m_id);
    }

    EXPECT_EQ(songs[0].id, 1);
    EXPECT_EQ(songs[0].name, "Window");
}

#endif  // TESTS_INTTESTS_TEST_PLAYLIST_USE_CASE_H_
