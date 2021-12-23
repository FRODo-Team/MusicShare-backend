// Owners: Rostislav Vivcharuk, WEB-12
#ifndef MUS_INTERNAL_MUS_MODELS_SONG_H_
#define MUS_INTERNAL_MUS_MODELS_SONG_H_

#include <string>
#include <optional>

namespace music_share {

class Song {
public:
    Song() = delete;

    Song(const std::string& title,
         const std::string& artist,
         const std::string& duration,
         const std::string& url,
         std::optional<uint32_t> year = { },
         const std::optional<std::string>& album = { },
         const std::optional<std::string>& genre = { },
         std::optional<uint32_t> id = { });

    Song(const Song&) = default;
    Song(const Song& other, uint32_t id);
    Song(Song&&) = default;
    ~Song() = default;

    Song& operator=(const Song&) = default;

    std::optional<uint32_t> GetId() const { return m_id; }
    const std::string& GetTitle() const { return m_title; }
    const std::string& GetArtist() const { return m_artist; }
    const std::optional<std::string>& GetAlbum() const { return m_album; }
    const std::optional<std::string>& GetGenre() const { return m_genre; }
    std::optional<uint32_t> GetYear() const { return m_year; }
    const std::string& GetDuration() const { return m_duration; }
    const std::string& GetUrl() const { return m_url; }

    void SetTitle(const std::string& title);
    void SetArtist(const std::string& artist);
    void SetAlbum(const std::optional<std::string>& album);
    void SetGenre(const std::optional<std::string>& genre);
    void SetYear(std::optional<uint32_t> year);
    void SetDuration(const std::string& duration);
    void SetUrl(const std::string& url);

private:
    std::string m_title;
    std::string m_artist;
    std::string m_duration;
    std::string m_url;
    std::optional<uint32_t> m_year;
    std::optional<std::string> m_album;
    std::optional<std::string> m_genre;
    std::optional<uint32_t> m_id;

    static constexpr uint32_t kAlbumMaxLength = 120;
    static constexpr uint32_t kGenreMaxLength = 30;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_MODELS_SONG_H_
