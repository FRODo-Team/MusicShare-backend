#include "mus-models/song.h"

namespace music_share {

Song::Song(const std::string &title,
           const std::string &artist,
           const std::string &duration,
           const std::string &url,
           std::optional<uint32_t> year,
           const std::optional<std::string> &album,
           const std::optional<std::string> &genre,
           std::optional<uint32_t> id)
        :
        m_title(title),
        m_artist(artist),
        m_duration(duration),
        m_url(url),
        m_year(year),
        m_album(album),
        m_genre(genre),
        m_id(id) { }

Song::Song(const Song& other, uint32_t id)
        :
        m_title(other.GetTitle()),
        m_artist(other.GetArtist()),
        m_duration(other.GetDuration()),
        m_url(other.GetUrl()),
        m_year(other.GetYear()),
        m_album(other.GetArtist()),
        m_genre(other.GetGenre()),
        m_id(id) { }

void Song::SetTitle(const std::string &title) {
    if (!title.empty()) {
        m_title = title;
    }
}

void Song::SetArtist(const std::string &artist) {
    if (!artist.empty()) {
        m_artist = artist;
    }
}

void Song::SetAlbum(const std::optional<std::string>& album) {
    if (album) {
        if (album->size() <= kAlbumMaxLength) {
            m_album = album;
        }
    } else {
        m_album = album;
    }
}

void Song::SetGenre(const std::optional<std::string>& genre) {
    if (genre) {
        if (genre->size() <= kGenreMaxLength) {
            m_genre = genre;
        }
    } else {
        m_genre = genre;
    }
}

void Song::SetYear(std::optional<uint32_t> year) {
    m_year = year;
}

void Song::SetDuration(const std::string &duration) {
    if (!duration.empty()) {
        m_duration = duration;
    }
}

void Song::SetUrl(const std::string &url) {
    m_url = url;
}

} // namespace music_share
