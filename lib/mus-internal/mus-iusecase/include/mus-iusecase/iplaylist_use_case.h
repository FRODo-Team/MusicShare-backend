// Oweners: Darya Vlaskina, ML-13
#ifndef MUS_INTERNAL_MUS_IUSECASE_IPLAYLIST_USE_CASE_H_
#define MUS_INTERNAL_MUS_IUSECASE_IPLAYLIST_USE_CASE_H_

#include <optional>
#include <vector>

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

    virtual uint32_t Create(uint32_t user_id,
                            const PlaylistRequestDTO& playlist_dto) = 0;

    virtual void DeleteById(uint32_t user_id, uint32_t playlist_id) = 0;

    virtual void AddSongById(const PlaylistSongRequestDTO& song_dto,
                             uint32_t playlist_id,
                             uint32_t user_id) = 0;

    virtual void DeleteSongById(uint32_t song_id, uint32_t playlist_id,
                                uint32_t user_id) = 0;

    virtual std::vector<PlaylistResponseDTO> GetByUserId(uint32_t user_id) const = 0;

    virtual PlaylistResponseDTO GetById(uint32_t id) const = 0;

    virtual std::vector<uint32_t> GetSongs(uint32_t playlist_id) const = 0;

    virtual ~IPlaylistUseCase() = default;
};

} // namespace music_share

#endif  // MUS_INTERNAL_MUS_IUSECASE_IPLAYLIST_USE_CASE_H_
