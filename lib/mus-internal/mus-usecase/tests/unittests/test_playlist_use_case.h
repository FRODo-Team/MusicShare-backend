// Oweners: Darya Vlaskina, ML-13
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <vector>
#include <string>
#include <utility>

#include "mus-iusecase/iplaylist_use_case.h"
#include "mus-irepo/iplaylist_repository.h"
#include "mus-iusecase/isong_use_case.h"
#include "mus-usecase/playlist_use_case.h"
#include "mus-dto/playlist_request_dto.h"
#include "mus-usecase/exception/access_exception.h"
#include "mus-usecase/exception/create_exception.h"
#include "mus-usecase/exception/exist_exception.h"
#include "mus-usecase/exception/invalid_data_exception.h"
#include "mus-usecase/exception/null_pointer_exception.h"
#include "mock/mock_playlist_repository.h"
#include "mock/mock_song_usecase.h"

using ::testing::AtLeast;
using testing::Invoke;
using testing::Return;

using std::make_shared;
using std::nullopt;
using std::optional;
using std::shared_ptr;
using std::string;
using std::vector;

using music_share::AccessException;
using music_share::CreateException;
using music_share::ExistException;
using music_share::InvalidDataException;
using music_share::NullPointerException;
using music_share::IPlaylistRepository;
using music_share::ISongUseCase;
using music_share::Playlist;
using music_share::PlaylistUseCase;

MATCHER_P(PlaylistEqualement, other, "Equality matcher for type Playlist") {
    return arg.GetTitle() == other.GetTitle();
}

class TestPlaylistUseCase : public ::testing::Test {
protected:
    void SetUp() {
        playlist_rep = make_shared<MockPlaylistRepository>();
        song_usecase = make_shared<MockSongUseCase>();
        playlist_usecase = make_shared<PlaylistUseCase>(*playlist_rep,
                                                        *song_usecase);

        vector<uint32_t> song_ids(1, 1);
        song_dto = make_shared<PlaylistSongRequestDTO>(song_ids);
        playlist = make_shared<Playlist>("playlist", 1,
                                         song_ids, 1);

        playlist_request = make_shared<PlaylistRequestDTO>("playlist",
                                                           *song_dto);
    }

    void TearDown() { }

    shared_ptr<PlaylistUseCase> playlist_usecase;
    shared_ptr<MockPlaylistRepository> playlist_rep;
    shared_ptr<MockSongUseCase> song_usecase;
    shared_ptr<Playlist> playlist;
    shared_ptr<PlaylistRequestDTO> playlist_request;
    shared_ptr<PlaylistSongRequestDTO> song_dto;
};

TEST_F(TestPlaylistUseCase, CreateSuccess) {
    uint32_t id_expected = 1;

    EXPECT_CALL(*playlist_rep, Insert(PlaylistEqualement(*playlist)))
            .WillOnce(Invoke([this](Playlist& playlist_out) {
                vector<uint32_t> song_ids(1, 2);
                playlist_out = *this->playlist;
            }));

    EXPECT_EQ(playlist_usecase->Create(1, *playlist_request),
              id_expected);
}

TEST_F(TestPlaylistUseCase, CreateException) {
    EXPECT_CALL(*playlist_rep, Insert(PlaylistEqualement(*playlist)))
                    .Times(AtLeast(1));

    EXPECT_THROW(playlist_usecase->Create(1, *playlist_request),
                 CreateException);
}

TEST_F(TestPlaylistUseCase, DeleteSuccess) {
    EXPECT_CALL(*playlist_rep, Find(1))
            .WillOnce(Return(*playlist));

    EXPECT_CALL(*playlist_rep, Delete(PlaylistEqualement(*playlist)))
            .Times(AtLeast(1));

    playlist_usecase->DeleteById(1, 1);
}

TEST_F(TestPlaylistUseCase, DeleteInvalidData) {
    EXPECT_CALL(*playlist_rep, Find(1))
            .WillOnce(Return(nullopt));

    playlist_usecase->DeleteById(1, 1);
}

TEST_F(TestPlaylistUseCase, DeleteAccessException) {
    EXPECT_CALL(*playlist_rep, Find(1))
            .WillOnce(Return(*playlist));

    EXPECT_THROW(playlist_usecase->DeleteById(2, 1),
                 AccessException);
}

TEST_F(TestPlaylistUseCase, AddSongSuccess) {
    EXPECT_CALL(*playlist_rep, Find(1))
            .WillOnce(Return(*playlist));

    EXPECT_CALL(*playlist_rep, Update(PlaylistEqualement(*playlist)))
            .Times(AtLeast(1));

    playlist_usecase->AddSongById(*song_dto, 1, 1);
}

TEST_F(TestPlaylistUseCase, AddSongInvalidData) {
    EXPECT_CALL(*playlist_rep, Find(1))
            .WillOnce(Return(nullopt));

    EXPECT_THROW(playlist_usecase->AddSongById(*song_dto, 1, 1),
                 InvalidDataException);
}

TEST_F(TestPlaylistUseCase, AddSongAccessException) {
    EXPECT_CALL(*playlist_rep, Find(1))
            .WillOnce(Return(*playlist));

    EXPECT_THROW(playlist_usecase->AddSongById(*song_dto, 1, 2),
                 AccessException);
}

TEST_F(TestPlaylistUseCase, DeleteSongSuccess) {
    EXPECT_CALL(*playlist_rep, Find(1))
            .WillOnce(Return(*playlist));

    EXPECT_CALL(*playlist_rep, Update(PlaylistEqualement(*playlist)))
            .Times(AtLeast(1));

    playlist_usecase->DeleteSongById(1, 1, 1);
}

TEST_F(TestPlaylistUseCase, DeleteSongInvalidData) {
    EXPECT_CALL(*playlist_rep, Find(1))
            .WillOnce(Return(nullopt));

    playlist_usecase->DeleteSongById(1, 1, 1);
}

TEST_F(TestPlaylistUseCase, DeleteSongAccessException) {
    EXPECT_CALL(*playlist_rep, Find(1))
            .WillOnce(Return(*playlist));

    EXPECT_THROW(playlist_usecase->DeleteSongById(1, 1, 2),
                 AccessException);
}

TEST_F(TestPlaylistUseCase, GetByUserIdSuccess) {
    vector<Playlist> playlists;
    playlists.push_back(*playlist);
    std::vector<SongResponseDTO> songs_dto;
    songs_dto.emplace_back(1, "song",
                           "artist", "path");
    PlaylistResponseDTO playlist_response_expected(1, 1,
                                                   1,
                                                   "playlist",
                                                   songs_dto);

    EXPECT_CALL(*song_usecase, GetById(1))
            .WillOnce(Return(songs_dto[0]));
    EXPECT_CALL(*playlist_rep, FindByUserId(1))
            .WillOnce(Return(playlists));

    vector<PlaylistResponseDTO> playlist_response
                                = playlist_usecase->GetByUserId(1);

    EXPECT_EQ(playlist_response[0].id, playlist_response_expected.id);
    EXPECT_EQ(playlist_response[0].author_id,
              playlist_response_expected.author_id);
    EXPECT_EQ(playlist_response[0].songs_count,
              playlist_response_expected.songs_count);
    EXPECT_EQ(playlist_response[0].title,
              playlist_response_expected.title);
    EXPECT_EQ(playlist_response[0].title,
              playlist_response_expected.title);
    EXPECT_EQ(playlist_response[0].songs_dto[0].id,
              songs_dto[0].id);
    EXPECT_EQ(playlist_response[0].songs_dto[0].path,
              songs_dto[0].path);
}

TEST_F(TestPlaylistUseCase, GetByUserIdInvalidData) {
    vector<Playlist> playlists;

    EXPECT_CALL(*playlist_rep, FindByUserId(1))
            .WillOnce(Return(playlists));

    vector<PlaylistResponseDTO> playlists_response = playlist_usecase->GetByUserId(1);

    EXPECT_TRUE(playlists_response.empty());
}

TEST_F(TestPlaylistUseCase, GetByUserIdNullPointer) {
    vector<uint32_t> song_ids(1);
    vector<Playlist> playlists;
    playlists.emplace_back("playlist", 1,
                           song_ids, nullopt);

    EXPECT_CALL(*playlist_rep, FindByUserId(1))
            .WillOnce(Return(playlists));

    EXPECT_THROW(playlist_usecase->GetByUserId(1),
                 NullPointerException);
}

TEST_F(TestPlaylistUseCase, GetByIdSuccess) {
    std::vector<SongResponseDTO> songs_dto;
    songs_dto.emplace_back(1, "song",
                        "artist", "path");
    PlaylistResponseDTO playlist_response_expected(1, 1,
                                                   1,
                                                   "playlist",
                                                   songs_dto);

    EXPECT_CALL(*playlist_rep, Find(1))
            .WillOnce(Return(*playlist));
    EXPECT_CALL(*song_usecase, GetById(1))
            .WillOnce(Return(songs_dto[0]));

    PlaylistResponseDTO playlist_response = playlist_usecase->GetById(1);

    EXPECT_EQ(playlist_response.id, playlist_response_expected.id);
    EXPECT_EQ(playlist_response.author_id,
              playlist_response_expected.author_id);
    EXPECT_EQ(playlist_response.songs_count,
              playlist_response_expected.songs_count);
    EXPECT_EQ(playlist_response.title,
              playlist_response_expected.title);
    EXPECT_EQ(playlist_response.songs_dto[0].id,
              songs_dto[0].id);
    EXPECT_EQ(playlist_response.songs_dto[0].path,
              songs_dto[0].path);
}

TEST_F(TestPlaylistUseCase, GetByIdInvalidData) {
    EXPECT_CALL(*playlist_rep, Find(1))
            .WillOnce(Return(nullopt));

    EXPECT_THROW(playlist_usecase->GetById(1),
                 InvalidDataException);
}

TEST_F(TestPlaylistUseCase, GetByIdNullPointer) {
    vector<uint32_t> song_ids(1);

    EXPECT_CALL(*playlist_rep, Find(1))
            .WillOnce(Return(Playlist("playlist", 1,
                                      song_ids, nullopt)));

    EXPECT_THROW(playlist_usecase->GetById(1),
                 NullPointerException);
}
