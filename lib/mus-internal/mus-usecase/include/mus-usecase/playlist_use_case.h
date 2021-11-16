#ifndef MUS_INTERNAL_MUS_USECASE_PLAYLIST_USE_CASE_H_
#define MUS_INTERNAL_MUS_USECASE_PLAYLIST_USE_CASE_H_

#include "iplaylist_use_case.h"

class PlaylistUseCase : IPlaylistUseCase {
public:
    PlaylistUseCase() = delete;

    PlaylistUseCase(IPlaylistReprositoriy& playlist_rep);

    PlaylistUseCase(const PlaylistUseCase& playlist_use_case);

    virtual PlaylistUseCase& operator=(const PlaylistUseCase& playlist_use_case);

    ~PlaylistUseCase();

    bool Create(int user_id, PlaylistRequestDTO playlist) override;

    bool DeleteById(int id_user, int id_playlist) override;

    bool AddSongById(PlaylistSongRequestDTO song, int id_playlist,
                     int id_user) override;

    bool DeleteSongById(int id_song, int id_playlist, int id_user) override;

    vector<PlaylistResponseDTO> GetByUserId(int id_user,
                                                                    int id_author) override;

    std::optional<PlaylistResponseDTO> GetById(int id) override;

    vector<SongResponseDTO> GetSongs(int id_playlist) override;

private:
    IPlaylistReprositoriy& m_playlist_rep;
};

#endif  // MUS_INTERNAL_MUS_USECASE_PLAYLIST_USE_CASE_H_
