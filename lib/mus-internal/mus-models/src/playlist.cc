#include "mus-models/playlist.h"

namespace music_share {

Playlist::Playlist(const std::string &title,
                   uint32_t creator_id,
                   const std::vector<uint32_t> &song_ids,
                   std::optional<uint32_t> id)
        :
        m_title(title),
        m_creator_id(creator_id),
        m_song_ids(song_ids),
        m_id(id) { }

Playlist::Playlist(const Playlist& other, uint32_t id)
        :
        m_title(other.GetTitle()),
        m_creator_id(other.GetCreatorId()),
        m_song_ids(other.GetSongIds()),
        m_id(id) { }

void Playlist::SetCreatorId(uint32_t creator_id) {
    m_creator_id = creator_id;
}

void Playlist::SetTitle(const std::string &title) {
    m_title = title;
}

void Playlist::SetSongIds(const std::vector<uint32_t>& songs) {
    m_song_ids = songs;
}

void Playlist::AppendSong(uint32_t song_id) {
    auto iter = std::find(m_song_ids.begin(), m_song_ids.end(), song_id);
    if (iter == m_song_ids.end()) {
        m_song_ids.push_back(song_id);
    }
}

void Playlist::RemoveSong(uint32_t song_id) {
    auto iter = std::find(m_song_ids.begin(), m_song_ids.end(), song_id);
    if (iter != m_song_ids.end()) {
        m_song_ids.erase(iter);
    }
}

} // namespace music_share
