#ifndef MUS_INTERNAL_MUS_IUSECASE_IPLAYLIST_USE_CASE_H_
#define MUS_INTERNAL_MUS_IUSECASE_IPLAYLIST_USE_CASE_H_

#include <cstdint>
#include <vector>

#include "playlist_request_dto.h"
#include "playlist_song_request_dto.h"
#include "playlist_response_dto.h"
#include "song_response_dto.h"

class IPlaylistUseCase {
public:
    IPlaylistUseCase() = default;

    IPlaylistUseCase(const IPlaylistUseCase& playlist_use_case) = default;

    IPlaylistUseCase& operator=(const IPlaylistUseCase& playlist_use_case) = default;

    virtual std::optional<uint32_t> Create(uint32_t user_id, PlaylistRequestDTO playlist) = 0;

    virtual bool DeleteById(uint32_t id_user, uint32_t id_playlist) = 0;

    virtual bool AddSongById(PlaylistSongRequestDTO song, uint32_t id_playlist,
                             uint32_t id_user) = 0;

    virtual bool DeleteSongById(uint32_t id_song, uint32_t id_playlist,
                                uint32_t id_user) = 0;

    virtual  vector<PlaylistResponseDTO> GetByUserId(uint32_t id_user,
                                                     uint32_t id_author) = 0;

    virtual  std::optional<PlaylistResponseDTO> GetById(uint32_t id) = 0;

    virtual  vector<SongResponseDTO> GetSongs(uint32_t id_playlist) = 0;

    virtual ~IPlaylistUseCase() {};
};

#endif  // MUS_INTERNAL_MUS_IUSECASE_IPLAYLIST_USE_CASE_H_
