#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <vector>
#include <string>
#include <utility>

#include "mus-iusecase/isong_use_case.h"
#include "mus-irepo/isong_repository.h"
#include "mus-usecase/song_use_case.h"
#include "mus-dto/song_response_dto.h"
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
using music_share::ISongRepository;
using music_share::Song;
using music_share::SongUseCase;

class MockSongRepository : public ISongRepository {
public:
    MOCK_METHOD1(FindByTitle, vector<Song>(const string&));
    MOCK_METHOD1(FindByArtist, vector<Song>(const string&));
    MOCK_METHOD1(Find, optional<Song>(uint32_t));
    MOCK_METHOD1(Insert, void(Song&));
    MOCK_METHOD1(Update, void(const Song&));
    MOCK_METHOD1(Delete, void(const Song&));
};

class TestSongUseCase : public ::testing::Test {
protected:
    void SetUp() {
        song_rep = make_shared<MockSongRepository>();
        song_usecase = make_shared<SongUseCase>(*song_rep);

        vector<uint32_t> song_ids(2, 2);
        song = make_shared<Song>("song", "artist",
                                 "duration", "url",
                                 1990, "album",
                                 "genre", 1);

    }

    void TearDown() { }

    shared_ptr<SongUseCase> song_usecase;
    shared_ptr<MockSongRepository> song_rep;
    shared_ptr<Song> song;
};

TEST_F(TestSongUseCase, GetByIdSuccess) {
    SongResponseDTO song_response_expected(1, "song",
                                      "artist", "url");

    EXPECT_CALL(*song_rep, Find(1))
            .WillOnce(Return(*song));

    SongResponseDTO song_response = song_usecase->GetById(1);

    EXPECT_EQ(song_response.id, song_response_expected.id);
    EXPECT_EQ(song_response.name, song_response_expected.name);
    EXPECT_EQ(song_response.author, song_response_expected.author);
    EXPECT_EQ(song_response.path, song_response_expected.path);
}

TEST_F(TestSongUseCase, GetByIdInvalidData) {
    EXPECT_CALL(*song_rep, Find(1))
            .WillOnce(Return(nullopt));

    EXPECT_THROW(song_usecase->GetById(1),
                 InvalidDataException);
}

TEST_F(TestSongUseCase, GetByIdNullPointer) {
    EXPECT_CALL(*song_rep, Find(1))
            .WillOnce(Return(Song("song", "artist",
                                  "duration", "url",
                                  1990, "album",
                                  "genre", nullopt)));

    EXPECT_THROW(song_usecase->GetById(1),
                 NullPointerException);
}

TEST_F(TestSongUseCase, GetByTitleSuccess) {
    SongResponseDTO song_response_expected(1, "song",
                                           "artist", "url");
    vector<Song> songs;
    songs.push_back(*song);

    EXPECT_CALL(*song_rep, FindByTitle("song"))
            .WillOnce(Return(songs));

    vector<SongResponseDTO> song_response = song_usecase->GetByTitle("song");

    EXPECT_EQ(song_response.size(), 1);
    EXPECT_EQ(song_response[0].id, song_response_expected.id);
    EXPECT_EQ(song_response[0].name, song_response_expected.name);
    EXPECT_EQ(song_response[0].author, song_response_expected.author);
    EXPECT_EQ(song_response[0].path, song_response_expected.path);
}

TEST_F(TestSongUseCase, GetByTitleInvalidData) {
    vector<Song> songs;

    EXPECT_CALL(*song_rep, FindByTitle("song"))
            .WillOnce(Return(songs));

    EXPECT_THROW(song_usecase->GetByTitle("song"),
                 InvalidDataException);
}

TEST_F(TestSongUseCase, GetByTitleNullPointer) {
    vector<Song> songs;
    songs.emplace_back("song", "artist",
                       "duration", "url",
                       1990, "album",
                       "genre", nullopt);

    EXPECT_CALL(*song_rep, FindByTitle("song"))
            .WillOnce(Return(songs));

    EXPECT_THROW(song_usecase->GetByTitle("song"),
                 NullPointerException);
}

TEST_F(TestSongUseCase, GetByArtistSuccess) {
    SongResponseDTO song_response_expected(1, "song",
                                           "artist", "url");
    vector<Song> songs;
    songs.push_back(*song);

    EXPECT_CALL(*song_rep, FindByArtist("artist"))
            .WillOnce(Return(songs));

    vector<SongResponseDTO> song_response = song_usecase->GetByArtist("artist");

    EXPECT_EQ(song_response.size(), 1);
    EXPECT_EQ(song_response[0].id, song_response_expected.id);
    EXPECT_EQ(song_response[0].name, song_response_expected.name);
    EXPECT_EQ(song_response[0].author, song_response_expected.author);
    EXPECT_EQ(song_response[0].path, song_response_expected.path);
}

TEST_F(TestSongUseCase, GetByArtistInvalidData) {
    vector<Song> songs;

    EXPECT_CALL(*song_rep, FindByArtist("artist"))
            .WillOnce(Return(songs));

    EXPECT_THROW(song_usecase->GetByArtist("artist"),
                 InvalidDataException);
}

TEST_F(TestSongUseCase, GetByArtistNullPointer) {
    vector<Song> songs;
    songs.emplace_back("song", "artist",
                       "duration", "url",
                       1990, "album",
                       "genre", nullopt);

    EXPECT_CALL(*song_rep, FindByArtist("artist"))
            .WillOnce(Return(songs));

    EXPECT_THROW(song_usecase->GetByArtist("artist"),
                 NullPointerException);
}
