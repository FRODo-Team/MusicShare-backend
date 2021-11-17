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
         std::optional<uint32_t> year = {},
         const std::optional<std::string>& album = {},
         const std::optional<std::string>& genre = {},
         std::optional<uint32_t> id = {});
    Song(const Song&) = default;
    Song(Song&&) = default;
    ~Song() = default;

    std::optional<uint32_t> GetId() const;
    const std::string& GetTitle() const;
    const std::string& GetArtist() const;
    const std::optional<std::string>& GetAlbum() const;
    const std::optional<std::string>& GetGenre() const;
    std::optional<uint32_t> GetYear() const;
    const std::string& GetDuration() const;
    const std::string& GetUrl() const;

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
