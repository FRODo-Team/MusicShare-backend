#ifndef MUS_INTERNAL_MUS_MODELS_CHAT_MESSAGE_H_
#define MUS_INTERNAL_MUS_MODELS_CHAT_MESSAGE_H_

#include <string>
#include <optional>

namespace music_share {

class ChatMessage {
public:
    ChatMessage() = delete;

    ChatMessage(uint32_t sender_id,
                const std::string& datetime,
                const std::string& content,
                uint32_t chat_id,
                std::optional<uint32_t> id = { });

    ChatMessage(const ChatMessage&) = default;
    ChatMessage(const ChatMessage& other, uint32_t id);
    ChatMessage(ChatMessage&&) = default;
    ~ChatMessage() = default;

    ChatMessage& operator=(const ChatMessage&) = default;

    std::optional<uint32_t> GetId() const { return m_id; }
    uint32_t GetSenderId() const { return m_sender_id; }
    const std::string& GetDatetime() const { return m_datetime; }
    const std::string& GetContent() const { return m_content; }
    uint32_t GetChatId() const { return m_chat_id; }

    void SetDatetime(const std::string& datetime);
    void SetContent(const std::string& content);
    void AppendContent(const std::string& content);

private:
    uint32_t m_sender_id;
    std::string m_datetime;
    std::string m_content;
    uint32_t m_chat_id;
    std::optional<uint32_t> m_id;
};

} // namespace music_share

#endif // MUS_INTERNAL_MUS_MODELS_CHAT_MESSAGE_H_
