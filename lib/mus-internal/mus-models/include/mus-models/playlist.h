#ifndef MUS_INTERNAL_MUS_MODELS_PLAYLIST_H_
#define MUS_INTERNAL_MUS_MODELS_PLAYLIST_H_

#include <string>
#include <vector>
#include <optional>

namespace music_share {

class Playlist {
public:
    Playlist() = delete;
    Playlist(uint32_t creator_id,
             const std::string& title,
             const std::vector<uint32_t>& song_ids,
             std::optional<uint32_t> id = {});
    Playlist(const Playlist&) = default;
    Playlist(Playlist&&) = default;
    ~Playlist() = default;

    std::optional<uint32_t> GetId() const;
    uint32_t GetCreatorId() const;
    const std::string& GetTitle() const;
    const std::vector<uint32_t>& GetSongIds() const;

    void SetCreatorId(uint32_t creator_id);
    void SetTitle(const std::string& title);

    void AppendSong(uint32_t song_id);
    void RemoveSong(uint32_t song_id);

private:
    uint32_t m_creator_id;
    std::string m_title;
    std::vector<uint32_t> m_song_ids;
    std::optional<uint32_t> m_id;

    static constexpr uint32_t kTitleMaxLength = 30;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_MODELS_PLAYLIST_H_
