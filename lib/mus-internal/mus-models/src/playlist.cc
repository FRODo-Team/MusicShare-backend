#include "mus_models/playlist.h"

namespace music_share {

Playlist::Playlist(uint32_t creator_id,
                   const std::string &title,
                   const std::vector<uint32_t> &song_ids,
                   std::optional<uint32_t> id) :
    m_creator_id(creator_id),
    m_title(title),
    m_song_ids(song_ids),
    m_id(id) { }

std::optional<uint32_t> Playlist::GetId() const {
    return m_id;
}

uint32_t Playlist::GetCreatorId() const {
    return m_creator_id;
}

const std::string &Playlist::GetTitle() const {
    return m_title;
}

const std::vector<uint32_t> &Playlist::GetSongIds() const {
    return m_song_ids;
}

void Playlist::SetCreatorId(uint32_t creator_id) {
    m_creator_id = creator_id;
}

void Playlist::SetTitle(const std::string &title) {
    m_title = title;
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
