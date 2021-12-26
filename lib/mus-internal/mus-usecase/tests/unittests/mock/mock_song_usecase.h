#ifndef MUS_INTERNAL_MOCK_MOCK_SONG_USECASE_H
#define MUS_INTERNAL_MOCK_MOCK_SONG_USECASE_H

#include <gmock/gmock.h>
#include <cstdint>
#include <vector>
#include <optional>
#include <string>

#include "mus-iusecase/isong_use_case.h"
#include "mus-dto/song_response_dto.h"

using std::string;
using std::optional;
using std::vector;

using music_share::ISongUseCase;

class MockSongUseCase : public ISongUseCase {
public:
    MOCK_CONST_METHOD1(GetById, SongResponseDTO(uint32_t));
    MOCK_CONST_METHOD2(GetByArtistAndTitle,
                       vector<SongResponseDTO>(const optional<string>,
                               const optional<string>));
};

#endif  // MUS_INTERNAL_MOCK_MOCK_SONG_USECASE_H
