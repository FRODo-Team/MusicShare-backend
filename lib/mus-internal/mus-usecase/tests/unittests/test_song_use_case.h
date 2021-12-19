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
#include "matcher/nullopt_matcher.h"

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
    MOCK_METHOD1(FetchAll, vector<Song>(optional<uint32_t>));
};

class TestSongUseCase : public ::testing::Test {
protected:
    void SetUp() {
        song_rep = make_shared<MockSongRepository>();
        song_usecase = make_shared<SongUseCase>(*song_rep);

        vector<uint32_t> song_ids(2, 2);
        first_song = make_shared<Song>("song", "artist",
                                 "duration", "url",
                                 1990, "album",
                                 "genre", 1);
        second_song = make_shared<Song>("song2", "artist2",
                                        "duration2", "url2",
                                        1999, "album", "genre", 2);
    }

    void TearDown() { }

    shared_ptr<SongUseCase> song_usecase;
    shared_ptr<MockSongRepository> song_rep;
    shared_ptr<Song> first_song;
    shared_ptr<Song> second_song;
};

TEST_F(TestSongUseCase, GetByIdSuccess) {
    SongResponseDTO song_response_expected(1, "song",
                                      "artist", "url");

    EXPECT_CALL(*song_rep, Find(1))
            .WillOnce(Return(*first_song));

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

TEST_F(TestSongUseCase, GetByTitle) {
    SongResponseDTO song_response_expected(1, "song",
                                           "artist", "url");
    vector<Song> songs;
    songs.push_back(*first_song);

    EXPECT_CALL(*song_rep, FindByTitle("song"))
            .WillOnce(Return(songs));

    vector<SongResponseDTO> song_response = song_usecase->GetByArtistAndTitle(nullopt,
                                                                              "song");

    EXPECT_EQ(song_response.size(), 1);
    EXPECT_EQ(song_response[0].id, song_response_expected.id);
    EXPECT_EQ(song_response[0].name, song_response_expected.name);
    EXPECT_EQ(song_response[0].author, song_response_expected.author);
    EXPECT_EQ(song_response[0].path, song_response_expected.path);
}

TEST_F(TestSongUseCase, GetByArtist) {
    SongResponseDTO song_response_expected(1, "song",
                                           "artist", "url");
    vector<Song> songs;
    songs.push_back(*first_song);

    EXPECT_CALL(*song_rep, FindByArtist("artist"))
            .WillOnce(Return(songs));

    vector<SongResponseDTO> song_response = song_usecase->GetByArtistAndTitle("artist",
                                                                              nullopt);

    EXPECT_EQ(song_response.size(), 1);
    EXPECT_EQ(song_response[0].id, song_response_expected.id);
    EXPECT_EQ(song_response[0].name, song_response_expected.name);
    EXPECT_EQ(song_response[0].author, song_response_expected.author);
    EXPECT_EQ(song_response[0].path, song_response_expected.path);
}

TEST_F(TestSongUseCase, GetByArtistAndTitleSuccess) {
    SongResponseDTO song_response_expected(1, "song",
                                           "artist", "url");
    vector<Song> songs;
    songs.push_back(*first_song);
    songs.push_back(*second_song);

    EXPECT_CALL(*song_rep, FindByArtist("artist"))
            .WillOnce(Return(songs));

    vector<SongResponseDTO> song_response = song_usecase->GetByArtistAndTitle("artist",
                                                                              "song");

    EXPECT_EQ(song_response.size(), 1);
    EXPECT_EQ(song_response[0].id, song_response_expected.id);
    EXPECT_EQ(song_response[0].name, song_response_expected.name);
    EXPECT_EQ(song_response[0].author, song_response_expected.author);
    EXPECT_EQ(song_response[0].path, song_response_expected.path);
}

TEST_F(TestSongUseCase, GetByArtistAndTitleEmptyRequest) {
    vector<SongResponseDTO> song_response_expected;
    song_response_expected.emplace_back(1, "song",
                                        "artist", "url");
    song_response_expected.emplace_back(2, "song2",
                                        "artist2", "url2");
    vector<Song> songs;
    songs.push_back(*first_song);
    songs.push_back(*second_song);

    EXPECT_CALL(*song_rep, FetchAll(NulloptEqualement(nullopt)))
            .WillOnce(Return(songs));

    vector<SongResponseDTO> song_response = song_usecase->GetByArtistAndTitle(nullopt,
                                                                              nullopt);

    EXPECT_EQ(song_response.size(), 2);
    EXPECT_EQ(song_response[0].id, song_response_expected[0].id);
    EXPECT_EQ(song_response[0].name, song_response_expected[0].name);
    EXPECT_EQ(song_response[0].author, song_response_expected[0].author);
    EXPECT_EQ(song_response[0].path, song_response_expected[0].path);
    EXPECT_EQ(song_response.size(), 2);
    EXPECT_EQ(song_response[1].id, song_response_expected[1].id);
    EXPECT_EQ(song_response[1].name, song_response_expected[1].name);
    EXPECT_EQ(song_response[1].author, song_response_expected[1].author);
    EXPECT_EQ(song_response[1].path, song_response_expected[1].path);
}

TEST_F(TestSongUseCase, GetByArtistAndTitleNotExist) {
    vector<Song> songs;

    EXPECT_CALL(*song_rep, FindByArtist("artist"))
            .WillOnce(Return(songs));

    vector<SongResponseDTO> songs_response = song_usecase->GetByArtistAndTitle("artist",
                                                                               "song");

    EXPECT_TRUE(songs_response.empty());
}

TEST_F(TestSongUseCase, GetByArtistAndTitleNullPointer) {
    vector<Song> songs;
    songs.emplace_back("song", "artist",
                    "duration", "url",
                    1990, "album",
                    "genre", nullopt);

    EXPECT_CALL(*song_rep, FindByArtist("artist"))
            .WillOnce(Return(songs));

    EXPECT_THROW(song_usecase->GetByArtistAndTitle("artist", "song"),
                 NullPointerException);
}


