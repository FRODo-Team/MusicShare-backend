#ifndef MUS_INTERNAL_MOCK_MOCK_PLAYLIST_REPOSITORY_H
#define MUS_INTERNAL_MOCK_MOCK_PLAYLIST_REPOSITORY_H

#include <gmock/gmock.h>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "mus-irepo/iplaylist_repository.h"
#include "mus-models/playlist.h"

using music_share::IPlaylistRepository;
using music_share::Playlist;
using std::string;
using std::optional;
using std::vector;

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

#endif  // MUS_INTERNAL_MOCK_MOCK_PLAYLIST_REPOSITORY_H
