#ifndef TESTS_INTTESTS_TEST_SONG_USE_CASE_H_
#define TESTS_INTTESTS_TEST_SONG_USE_CASE_H_

#include "gtest/gtest.h"

#include <cstdint>
#include <memory>
#include <vector>

#include "../mus-iusecase/isong_use_case.h"
#include "../mus-irepo/isong_repository.h"
#include "../mus-usecase/song_use_case.h"
#include "../mus-dto/song_response_dto.h"

using std::vector;
using std::string;
using std::shared_ptr;
using std::make_shared;
using music_share::ISongRepository;
using std::optional;
using music_share::SongUseCase;

class TestSongUseCase : public ::testing::Test {
protected:
    void SetUp() {
        shared_ptr<ISongRepository> song_rep = make_shared<SongRepositoryPostgres>(connection_to_database);
        m_song_use_case = make_shared<SongUseCase>(*song_rep);
    }
    void TearDown() { }

    shared_ptr<ISongUseCase> m_song_use_case;
};

TEST_F(TestSongUseCase, GetById) {
    optional<SongResponseDTO> song_response = m_song_use_case->GetById(0);

    string expected_title("Window");
    string expected_artist("Alexey");
    if (song_response) {
        EXPECT_EQ(song_response->name, expected_title);
        EXPECT_EQ(song_response->author, expected_artist);
    }
}

TEST_F(TestSongUseCase, GetByName) {
    string title("Window");

    vector<SongResponseDTO> songs = m_song_use_case->GetByTitle(title);

    string expected_artist("Alexey");
    EXPECT_EQ(songs[0].author, expected_artist);
}

TEST_F(TestSongUseCase, GetByAuthor) {
    string artist("Alexey");

    vector<SongResponseDTO> songs = m_song_use_case->GetByArtist(artist);

    string expected_title("Window");
    EXPECT_EQ(songs[0].name, expected_title);
}

#endif  // TESTS_INTTESTS_TEST_SONG_USE_CASE_H_
