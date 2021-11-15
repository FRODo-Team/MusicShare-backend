#ifndef MUS_INTERNAL_MUS_MODELS_CHAT_MESSAGE_H_
#define MUS_INTERNAL_MUS_MODELS_CHAT_MESSAGE_H_

#include <string>
#include <optional>

namespace music_share {

class ChatMessage {
public:
    ChatMessage() = delete;
    ChatMessage(uint32_t chat_id,
                uint32_t sender_id,
                const std::string& datetime,
                const std::string& content,
                std::optional<uint32_t> id = {});
    ChatMessage(const ChatMessage&) = default;
    ChatMessage(ChatMessage&&) = default;
    ~ChatMessage() = default;

    std::optional<uint32_t> GetId() const;
    uint32_t GetChatId() const;
    uint32_t GetSenderId() const;
    const std::string& GetDatetime() const;
    const std::string& GetContent() const;

    void SetDatetime(const std::string& datetime);
    void SetContent(const std::string& content);

    void AppendContent(const std::string& content);

private:
    uint32_t m_chat_id;
    uint32_t m_sender_id;
    std::string m_datetime;
    std::string m_content;
    std::optional<uint32_t> m_id;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_MODELS_CHAT_MESSAGE_H_
