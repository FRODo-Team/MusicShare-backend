#ifndef MUS_INTERNAL_MOCK_MUS_MOCK_PLAYLIST_USECASE_H
#define MUS_INTERNAL_MOCK_MUS_MOCK_PLAYLIST_USECASE_H

#include <gmock/gmock.h>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "mus-iusecase/iplaylist_use_case.h"

using music_share::IPlaylistUseCase;
using std::string;
using std::optional;
using std::vector;

class MockPlaylistUseCase : public IPlaylistUseCase {
public:
    MOCK_METHOD2(Create, uint32_t(uint32_t, const PlaylistRequestDTO&));
    MOCK_METHOD2(DeleteById, void(uint32_t, uint32_t));
    MOCK_METHOD3(AddSongById, void(const PlaylistSongRequestDTO&,
                                    uint32_t, uint32_t));
    MOCK_METHOD3(DeleteSongById, void(uint32_t, uint32_t, uint32_t));
    MOCK_CONST_METHOD1(GetByUserId, vector<PlaylistResponseDTO>(uint32_t));
    MOCK_CONST_METHOD1(GetById, PlaylistResponseDTO(uint32_t));
};

#endif  // MUS_INTERNAL_MOCK_MUS_MOCK_PLAYLIST_USECASE_H
