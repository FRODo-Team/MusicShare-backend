#include "mus-models/chat_message.h"

namespace music_share {

ChatMessage::ChatMessage(uint32_t sender_id,
                         const std::string& datetime,
                         const std::string& content,
                         uint32_t chat_id,
                         std::optional<uint32_t> id)
        :
        m_sender_id(sender_id),
        m_datetime(datetime),
        m_content(content),
        m_chat_id(chat_id),
        m_id(id) { }

void ChatMessage::SetDatetime(const std::string &datetime) {
    m_datetime = datetime;
}

void ChatMessage::SetContent(const std::string &content) {
    m_content = content;
}

void ChatMessage::AppendContent(const std::string &content) {
    m_content += content;
}


} // namespace music_share
