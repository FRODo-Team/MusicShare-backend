#ifndef MUS_INTERNAL_MUS_IUSECASE_IPLAYLIST_USE_CASE_H_
#define MUS_INTERNAL_MUS_IUSECASE_IPLAYLIST_USE_CASE_H_

#include <vector>
#include <optional>

#include "mus-dto/playlist_request_dto.h"
#include "mus-dto/playlist_song_request_dto.h"
#include "mus-dto/playlist_response_dto.h"
#include "mus-dto/song_response_dto.h"

namespace music_share {

class IPlaylistUseCase {
public:
    IPlaylistUseCase() = default;

    IPlaylistUseCase(const IPlaylistUseCase& playlist_use_case) = default;

    IPlaylistUseCase& operator=(const IPlaylistUseCase& playlist_use_case) = default;

    virtual std::optional<uint32_t> Create(uint32_t user_id,
                                           PlaylistRequestDTO playlist) = 0;

    virtual bool DeleteById(uint32_t user_id, uint32_t playlist_id) = 0;

    virtual bool AddSongById(PlaylistSongRequestDTO song, uint32_t playlist_id,
                             uint32_t user_id) = 0;

    virtual bool DeleteSongById(uint32_t song_id, uint32_t playlist_id,
                                uint32_t user_id) = 0;

    virtual  std::vector<PlaylistResponseDTO> GetByUserId(uint32_t user_id,
                                                          uint32_t author_id) = 0;

    virtual  std::optional<PlaylistResponseDTO> GetById(uint32_t id) = 0;

    virtual  std::vector<SongResponseDTO> GetSongs(uint32_t playlist_id) = 0;

    virtual ~IPlaylistUseCase() {};
};

} // namespace music_share

#endif  // MUS_INTERNAL_MUS_IUSECASE_IPLAYLIST_USE_CASE_H_
