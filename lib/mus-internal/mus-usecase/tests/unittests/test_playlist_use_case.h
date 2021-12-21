// Oweners: Darya Vlaskina, ML-13
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <vector>
#include <string>
#include <utility>

#include "mus-iusecase/iplaylist_use_case.h"
#include "mus-irepo/iplaylist_repository.h"
#include "mus-usecase/playlist_use_case.h"
#include "mus-dto/playlist_request_dto.h"
#include "mus-usecase/exception/access_exception.h"
#include "mus-usecase/exception/create_exception.h"
#include "mus-usecase/exception/exist_exception.h"
#include "mus-usecase/exception/invalid_data_exception.h"
#include "mus-usecase/exception/null_pointer_exception.h"

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
using music_share::Playlist;
using music_share::PlaylistUseCase;

class MockPlaylistRepository : public IPlaylistRepository {
public:
    MOCK_METHOD1(FindByTitle, vector<Playlist>(const string&));
    MOCK_METHOD1(FindByCreatorId, vector<Playlist>(uint32_t));
    MOCK_METHOD1(FindByUserId, vector<Playlist>(uint32_t));
    MOCK_METHOD1(Find, optional<Playlist>(uint32_t));
    MOCK_METHOD1(Insert, void(Playlist&));
    MOCK_METHOD1(Update, void(const Playlist&));
    MOCK_METHOD1(Delete, void(const Playlist&));
};

MATCHER_P(PlaylistEqualement, other, "Equality matcher for type Playlist") {
    return arg.GetTitle() == other.GetTitle();
}

class TestPlaylistUseCase : public ::testing::Test {
protected:
    void SetUp() {
        playlist_rep = make_shared<MockPlaylistRepository>();
        playlist_usecase = make_shared<PlaylistUseCase>(*playlist_rep);

        vector<uint32_t> song_ids(2, 2);
        playlist = make_shared<Playlist>("playlist", 1,
                                         song_ids, 1);

        playlist_request = make_shared<PlaylistRequestDTO>("playlist",
                                                           song_ids);

        song = make_shared<PlaylistSongRequestDTO>(song_ids);
    }

    void TearDown() { }

    shared_ptr<PlaylistUseCase> playlist_usecase;
    shared_ptr<MockPlaylistRepository> playlist_rep;
    shared_ptr<Playlist> playlist;
    shared_ptr<PlaylistRequestDTO> playlist_request;
    shared_ptr<PlaylistSongRequestDTO> song;
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

    playlist_usecase->AddSongById(*song, 1, 1);
}

TEST_F(TestPlaylistUseCase, AddSongInvalidData) {
    EXPECT_CALL(*playlist_rep, Find(1))
            .WillOnce(Return(nullopt));

    EXPECT_THROW(playlist_usecase->AddSongById(*song, 1, 1),
                 InvalidDataException);
}

TEST_F(TestPlaylistUseCase, AddSongAccessException) {
    EXPECT_CALL(*playlist_rep, Find(1))
            .WillOnce(Return(*playlist));

    EXPECT_THROW(playlist_usecase->AddSongById(*song, 1, 2),
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
    playlists.emplace_back(*playlist);
    PlaylistResponseDTO playlist_response_expected(1, 1,
                                                   2,
                                                   "playlist");

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
    PlaylistResponseDTO playlist_response_expected(1, 1,
                                                   2,
                                                   "playlist");

    EXPECT_CALL(*playlist_rep, Find(1))
            .WillOnce(Return(*playlist));

    PlaylistResponseDTO playlist_response = playlist_usecase->GetById(1);

    EXPECT_EQ(playlist_response.id, playlist_response_expected.id);
    EXPECT_EQ(playlist_response.author_id,
              playlist_response_expected.author_id);
    EXPECT_EQ(playlist_response.songs_count,
              playlist_response_expected.songs_count);
    EXPECT_EQ(playlist_response.title,
              playlist_response_expected.title);

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

TEST_F(TestPlaylistUseCase, GetSongsSuccess) {
    vector<uint32_t> song_response_expected(2, 2);

    EXPECT_CALL(*playlist_rep, Find(1))
            .WillOnce(Return(*playlist));

    vector<uint32_t> songs_response = playlist_usecase->GetSongs(1);

    EXPECT_EQ(song_response_expected.size(), songs_response.size());
    EXPECT_EQ(song_response_expected[0], songs_response[0]);
    EXPECT_EQ(song_response_expected[1], songs_response[1]);
}

TEST_F(TestPlaylistUseCase, GetSongsInvalidData) {
    EXPECT_CALL(*playlist_rep, Find(1))
            .WillOnce(Return(nullopt));

    vector<uint32_t> song_ids = playlist_usecase->GetSongs(1);

    EXPECT_TRUE(song_ids.empty());
}
