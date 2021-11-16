#ifndef MUS_INTERNAL_MUS_IUSECASE_IPLAYLIST_USE_CASE_H_
#define MUS_INTERNAL_MUS_IUSECASE_IPLAYLIST_USE_CASE_H_

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

    virtual bool Create(int user_id, PlaylistRequestDTO playlist) = 0;

    virtual bool DeleteById(int id_user, int id_playlist) = 0;

    virtual bool AddSongById(PlaylistSongRequestDTO song, int id_playlist,
                             int id_user) = 0;

    virtual bool DeleteSongById(int id_song, int id_playlist, int id_user) = 0;

    virtual  vector<PlaylistResponseDTO> GetByUserId(int id_user,
                                                     int id_author) = 0;

    virtual  std::optional<PlaylistResponseDTO> GetById(int id) = 0;

    virtual  vector<SongResponseDTO> GetSongs(int id_playlist) = 0;

    virtual ~IPlaylistUseCase() {};
};

#endif  // MUS_INTERNAL_MUS_IUSECASE_IPLAYLIST_USE_CASE_H_
