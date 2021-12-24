#include "mus-usecase/playlist_use_case.h"

#include <algorithm>
#include <memory>
#include <optional>

#include "mus-usecase/exception/access_exception.h"
#include "mus-usecase/exception/create_exception.h"
#include "mus-usecase/exception/invalid_data_exception.h"
#include "mus-usecase/exception/null_pointer_exception.h"

using std::back_inserter;
using std::make_unique;
using std::transform;
using std::nullopt;
using std::optional;
using std::string;
using std::unique_ptr;
using std::vector;

namespace  music_share {

    PlaylistUseCase::PlaylistUseCase(IPlaylistRepository& playlist_rep,
                                     ISongUseCase& song_usecase)
                                    : m_playlist_rep(playlist_rep),
                                    m_song_usecase(song_usecase) { }

    PlaylistUseCase::PlaylistUseCase(const PlaylistUseCase& playlist_use_case)
                : m_playlist_rep(playlist_use_case.m_playlist_rep),
                m_song_usecase(playlist_use_case.m_song_usecase) { }

    PlaylistUseCase &PlaylistUseCase::operator=(const PlaylistUseCase& playlist_usecase) {
        m_playlist_rep = playlist_usecase.m_playlist_rep;
        m_song_usecase = playlist_usecase.m_song_usecase;
        return *this;
    }

    uint32_t PlaylistUseCase::Create(uint32_t user_id,
                                     const PlaylistRequestDTO& playlist_dto) {
        Playlist playlist(playlist_dto.name,
                          user_id,
                          playlist_dto.song_dto.song_ids);

        m_playlist_rep.Insert(playlist);

        if (!playlist.GetId()) {
            throw CreateException();
        }
        return *playlist.GetId();
    }

    void PlaylistUseCase::DeleteById(uint32_t user_id,
                                     uint32_t playlist_id) {
        optional<Playlist> playlist = m_playlist_rep.Find(playlist_id);

        if (!playlist) {
            return;
        }
        if (playlist->GetCreatorId() != user_id) {
            throw AccessException();
        }

        m_playlist_rep.Delete(*playlist);
    }

    void PlaylistUseCase::AddSongById(const PlaylistSongRequestDTO& song,
                                      uint32_t playlist_id,
                                      uint32_t user_id) {
        optional<Playlist> playlist = m_playlist_rep.Find(playlist_id);

        if (!playlist) {
            throw InvalidDataException();
        }
        if (playlist->GetCreatorId() != user_id) {
            throw AccessException();
        }

        for (const uint32_t& id : song.song_ids) {
            playlist->AppendSong(id);
        }
        m_playlist_rep.Update(*playlist);
    }

    void PlaylistUseCase::DeleteSongById(uint32_t song_id,
                                         uint32_t playlist_id,
                                         uint32_t user_id) {
        optional<Playlist> playlist = m_playlist_rep.Find(playlist_id);

        if (!playlist) {
            return;
        }
        if (playlist->GetCreatorId() != user_id) {
            throw AccessException();
        }

        playlist->RemoveSong(song_id);
        m_playlist_rep.Update(*playlist);
    }

    vector<PlaylistResponseDTO> PlaylistUseCase::GetByUserId(uint32_t user_id) const {
        vector<Playlist> playlists = m_playlist_rep.FindByUserId(user_id);

        if (playlists.empty()) {
            return {};
        }

        vector<PlaylistResponseDTO> playlists_dto;
        playlists_dto.reserve(playlists.size());
        for (const Playlist& playlist : playlists) {
            if (!playlist.GetId()) {
                throw NullPointerException();
            }

            vector<SongResponseDTO> songs_dto = GetSongs(playlist.GetSongIds());
            playlists_dto.emplace_back(*playlist.GetId(),
                                       playlist.GetCreatorId(),
                                       static_cast<uint32_t>(songs_dto.size()),
                                       playlist.GetTitle(),
                                       songs_dto);
        }

        return playlists_dto;
    }

    PlaylistResponseDTO PlaylistUseCase::GetById(uint32_t id) const {
        optional<Playlist> playlist = m_playlist_rep.Find(id);

        if (!playlist) {
            throw InvalidDataException();
        }
        if (!playlist->GetId()) {
            throw NullPointerException();
        }

        vector<SongResponseDTO> songs_dto = GetSongs(playlist->GetSongIds());
        return PlaylistResponseDTO(*playlist->GetId(),
                                   playlist->GetCreatorId(),
                                   static_cast<uint32_t>(songs_dto.size()),
                                   playlist->GetTitle(),
                                   songs_dto);
    }

    vector<SongResponseDTO> PlaylistUseCase::GetSongs(const vector<uint32_t>& song_ids) const {
        vector<SongResponseDTO> songs_dto;
        songs_dto.reserve(song_ids.size());

        transform(song_ids.begin(), song_ids.end(),
                       back_inserter(songs_dto),
                       [this](auto song_id) {
                           return m_song_usecase.GetById(song_id);
        });

        return songs_dto;
    }

}  // namespace music_share
