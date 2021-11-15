#include "mus_models/song.h"

namespace music_share {

Song::Song(const std::string &title,
           const std::string &author,
           const std::string &duration,
           const std::string &url,
           std::optional<uint32_t> year,
           const std::optional<std::string> &album,
           const std::optional<std::string> &genre,
           std::optional<uint32_t> id) :
    m_title(title),
    m_author(author),
    m_duration(duration),
    m_url(url),
    m_year(year),
    m_album(album),
    m_genre(genre),
    m_id(id) { }

std::optional<uint32_t> Song::GetId() const {
    return m_id;
}

const std::string& Song::GetTitle() const {
    return m_title;
}

const std::string& Song::GetAuthor() const {
    return m_author;
}

const std::optional<std::string>& Song::GetAlbum() const {
    return m_album;
}

const std::optional <std::string>& Song::GetGenre() const {
    return m_genre;
}

std::optional<uint32_t> Song::GetYear() const {
    return m_year;
}

const std::string& Song::GetDuration() const {
    return m_duration;
}

const std::string& Song::GetUrl() const {
    return m_url;
}

void Song::SetTitle(const std::string &title) {
    if (!title.empty()) {
        m_title = title;
    }
}

void Song::SetAuthor(const std::string &author) {
    if (!author.empty()) {
        m_author = author;
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
