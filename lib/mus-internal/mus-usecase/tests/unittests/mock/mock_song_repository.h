#ifndef MUS_INTERNAL_MOCK_MOCK_SONG_REPOSITORY_H
#define MUS_INTERNAL_MOCK_MOCK_SONG_REPOSITORY_H

#include <gmock/gmock.h>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "mus-irepo/isong_repository.h"
#include "mus-models/song.h"

using std::string;
using std::optional;
using std::vector;

using music_share::ISongRepository;
using music_share::Song;

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

#endif  // MUS_INTERNAL_MOCK_MOCK_SONG_REPOSITORY_H
