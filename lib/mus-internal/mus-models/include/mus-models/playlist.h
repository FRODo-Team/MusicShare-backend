#ifndef MUS_INTERNAL_MUS_MODELS_PLAYLIST_H_
#define MUS_INTERNAL_MUS_MODELS_PLAYLIST_H_

#include <string>
#include <vector>
#include <optional>

namespace music_share {

class Playlist {
public:
    Playlist() = delete;

    Playlist(const std::string& title,
             uint32_t creator_id,
             const std::vector<uint32_t>& song_ids,
             std::optional<uint32_t> id = { });

    Playlist(const Playlist&) = default;
    Playlist(const Playlist& other, uint32_t id);
    Playlist(Playlist&&) = default;
    ~Playlist() = default;

    Playlist& operator=(const Playlist&) = default;

    std::optional<uint32_t> GetId() const { return m_id; }
    const std::string& GetTitle() const { return m_title; }
    uint32_t GetCreatorId() const { return m_creator_id; }
    const std::vector<uint32_t>& GetSongIds() const { return m_song_ids; }

    void SetCreatorId(uint32_t creator_id);
    void SetTitle(const std::string& title);
    void SetSongIds(const std::vector<uint32_t>& songs);

    void AppendSong(uint32_t song_id);
    void RemoveSong(uint32_t song_id);

private:
    std::string m_title;
    uint32_t m_creator_id;
    std::vector<uint32_t> m_song_ids;
    std::optional<uint32_t> m_id;

    static constexpr uint32_t kTitleMaxLength = 30;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_MODELS_PLAYLIST_H_
