#ifndef MUS_INTERNAL_MUS_USECASE_PLAYLIST_USE_CASE_H_
#define MUS_INTERNAL_MUS_USECASE_PLAYLIST_USE_CASE_H_

#include "iplaylist_use_case.h"
#include "iplaylist_repository.h"

class PlaylistUseCase : IPlaylistUseCase {
public:
    PlaylistUseCase() = delete;

    PlaylistUseCase(IPlaylistRepository& playlist_rep);

    PlaylistUseCase(const PlaylistUseCase& playlist_use_case);

    virtual PlaylistUseCase& operator=(const PlaylistUseCase& playlist_use_case);

    ~PlaylistUseCase();

    std::optional<uint32_t> Create(uint32_t user_id, PlaylistRequestDTO playlist) override;

    bool DeleteById(uint32_t id_user, uint32_t id_playlist) override;

    bool AddSongById(PlaylistSongRequestDTO song, uint32_t id_playlist,
                     uint32_t id_user) override;

    bool DeleteSongById(uint32_t id_song, uint32_t id_playlist, uint32_t id_user) override;

    vector<PlaylistResponseDTO> GetByUserId(uint32_t id_user,
                                            uint32_t id_author) override;

    std::optional<PlaylistResponseDTO> GetById(uint32_t id) override;

    vector<SongResponseDTO> GetSongs(uint32_t id_playlist) override;

private:
    IPlaylistRepository& m_playlist_rep;
};

#endif  // MUS_INTERNAL_MUS_USECASE_PLAYLIST_USE_CASE_H_
