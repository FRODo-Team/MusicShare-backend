#include "mus-usecase/chat_message_use_case.h"

#include <chrono>
#include <memory>
#include <optional>

#include "mus-usecase/exception/access_exception.h"
#include "mus-usecase/exception/create_exception.h"
#include "mus-usecase/exception/invalid_data_exception.h"
#include "mus-usecase/exception/null_pointer_exception.h"

using std::ctime;
using std::make_unique;
using std::optional;
using std::string;
using std::vector;
using std::time_t;

namespace music_share {

    ChatMessageUseCase::ChatMessageUseCase(IChatMessageRepository& chat_message_rep)
                                            : m_chat_message_rep(chat_message_rep) { }

    ChatMessageUseCase::ChatMessageUseCase(const ChatMessageUseCase& chat_message_use_case)
                                            : m_chat_message_rep(chat_message_use_case.m_chat_message_rep) { }

    ChatMessageUseCase& ChatMessageUseCase::operator=(const ChatMessageUseCase& chat_message_use_case) {
        m_chat_message_rep = chat_message_use_case.m_chat_message_rep;
        return *this;
    }

    uint32_t ChatMessageUseCase::SendMessage(const MessageRequestDTO& message_dto, uint32_t chat_id,
                                             uint32_t user_id,
                                             optional<string> datetime) {
        if (!datetime) {
            auto time = std::chrono::system_clock::now();
            time_t end_time = std::chrono::system_clock::to_time_t(time);
            datetime = ctime(&end_time);
        }

        auto message = make_unique<ChatMessage>(user_id,
                                                *datetime,
                                                message_dto.content,
                                                chat_id);
        m_chat_message_rep.Insert(*message);

        if (!message->GetId()) {
            throw CreateException();
        }
        return *message->GetId();
    }

    vector<MessageResponseDTO> ChatMessageUseCase::GetUserMessages(uint32_t user_id,
                                                                   uint32_t chat_id) const {
        vector<ChatMessage> messages = m_chat_message_rep.FindByChatId(chat_id);

        if (messages.empty()) {
            throw InvalidDataException();
        }

        vector<MessageResponseDTO> messages_dto;
        messages_dto.reserve(messages.size());

        for (const ChatMessage& message : messages) {
            if (message.GetSenderId() != user_id) {
                continue;
            }
            if (!message.GetId()) {
                throw NullPointerException();
            }
            messages_dto.emplace_back(*message.GetId(),
                                      message.GetChatId(),
                                      message.GetSenderId(),
                                      message.GetContent(),
                                      message.GetDatetime());
        }

        return messages_dto;
    }

}  // namespace music_share
