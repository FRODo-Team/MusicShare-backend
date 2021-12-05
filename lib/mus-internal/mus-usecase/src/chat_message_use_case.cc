#include "mus-usecase/chat_message_use_case.h"

#include <memory>
#include <optional>

using std::make_unique;
using std::optional;
using std::string;
using std::vector;

namespace music_share {

    ChatMessageUseCase::ChatMessageUseCase(IChatMessageRepository& chat_message_rep)
                                            : m_chat_message_rep(chat_message_rep) { }

    ChatMessageUseCase::ChatMessageUseCase(const ChatMessageUseCase& chat_message_use_case)
                                            : m_chat_message_rep(chat_message_use_case.m_chat_message_rep) { }

    ChatMessageUseCase& ChatMessageUseCase::operator=(const ChatMessageUseCase& chat_message_use_case) {
        m_chat_message_rep = chat_message_use_case.m_chat_message_rep;
        return *this;
    }

    uint32_t ChatMessageUseCase::SendMessage(const MessageRequestDTO& message_request_dto,
                                         const string& datetime, uint32_t chat_id,
                                         uint32_t user_id) {
        auto message = make_unique<ChatMessage>(user_id,
                                                                    datetime,
                                                                    message_request_dto.content,
                                                                    chat_id);
        m_chat_message_rep.Insert(*message);

        if (!message->GetId()) {
            throw "Can`t create message";
        }
        return *message->GetId();
    }

    MessageResponseDTO ChatMessageUseCase::FindById(uint32_t id) {
        optional<ChatMessage> message = m_chat_message_rep.Find(id);

        if (!message) {
            throw "Message doesn`t exist";
        }
        if (!message->GetId()) {
            throw "Null id";
        }

        return MessageResponseDTO(*message->GetId(),
                                  message->GetChatId(),
                                  message->GetSenderId(),
                                  message->GetContent(),
                                  message->GetDatetime());
    }

    vector<MessageResponseDTO> ChatMessageUseCase::GetUserMessages(uint32_t user_id,
                                                                   uint32_t chat_id) {
        vector<ChatMessage> messages = m_chat_message_rep.FindByChatId(chat_id);

        if (messages.empty()) {
            throw "Message doesn`t exist";
        }

        vector<MessageResponseDTO> messages_dto;
        messages_dto.reserve(messages.size());
        for (const ChatMessage& message : messages) {
            if (message.GetSenderId() == user_id) {
                if (!message.GetId()) {
                    throw "Null id";
                }
                messages_dto.emplace_back(*message.GetId(),
                                       message.GetChatId(),
                                       message.GetSenderId(),
                                       message.GetContent(),
                                       message.GetDatetime());
            }
        }

        return messages_dto;
    }

    void ChatMessageUseCase::Delete(uint32_t user_id, uint32_t message_id) {
        optional<ChatMessage> message = m_chat_message_rep.Find(message_id);

        if (!message) {
            throw "Message doesn`t exist";
        }
        if (message->GetSenderId() != user_id) {
            throw "No access";
        }

        m_chat_message_rep.Delete(*message);
    }

    MessageResponseDTO ChatMessageUseCase::Update(uint32_t user_id, uint32_t message_id) {
        optional<ChatMessage> message = m_chat_message_rep.Find(message_id);

        if (!message) {
            throw "Message doesn`t exist";
        }
        if (message->GetSenderId() != user_id) {
            throw "No access";
        }

        m_chat_message_rep.Update(*message);

        return MessageResponseDTO(message_id,
                                  message->GetChatId(),
                                  message->GetSenderId(),
                                  message->GetContent(),
                                  message->GetDatetime() );
    }


}  // namespace music_share
