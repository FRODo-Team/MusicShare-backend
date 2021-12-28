// Oweners: Darya Vlaskina, ML-13
#include "mus-usecase/chat_message_use_case.h"

#include <chrono>
#include <memory>
#include <optional>

#include "mus-usecase/exception/access_exception.h"
#include "mus-usecase/exception/create_exception.h"
#include "mus-usecase/exception/null_pointer_exception.h"

using std::ctime;
using std::make_unique;
using std::optional;
using std::nullopt;
using std::string;
using std::vector;
using std::time_t;
using std::pair;

namespace music_share {

    ChatMessageUseCase::ChatMessageUseCase(IChatMessageRepository& chat_message_rep,
                                           IChatRepository& chat_rep,
                                           IPlaylistUseCase& playlist_usecase)
                                            : m_chat_message_rep(chat_message_rep),
                                            m_chat_rep(chat_rep),
                                            m_playlist_usecase(playlist_usecase) { }

    ChatMessageUseCase::ChatMessageUseCase(const ChatMessageUseCase& chat_message_use_case)
                                            : m_chat_message_rep(chat_message_use_case.m_chat_message_rep),
                                              m_chat_rep(chat_message_use_case.m_chat_rep),
                                              m_playlist_usecase(chat_message_use_case.m_playlist_usecase) { }

    ChatMessageUseCase& ChatMessageUseCase::operator=(const ChatMessageUseCase& chat_message_use_case) {
        m_chat_message_rep = chat_message_use_case.m_chat_message_rep;
        m_chat_rep = chat_message_use_case.m_chat_rep;
        m_playlist_usecase = chat_message_use_case.m_playlist_usecase;
        return *this;
    }

    uint32_t ChatMessageUseCase::SendMessage(const MessageRequestDTO& message_dto,
                                             uint32_t chat_id,
                                             uint32_t user_id,
                                             optional<string> datetime) {
        optional<bool> check_result = CheckAccess(chat_id, user_id);
        if (!check_result) {
            return {};
        }
        if (!*check_result) {
            throw AccessException();
        }

        if (!datetime) {
            auto time = std::chrono::system_clock::now();
            time_t end_time = std::chrono::system_clock::to_time_t(time);
            datetime = ctime(&end_time);
        }

        ChatMessage message(user_id,
                            *datetime,
                            message_dto.content,
                            chat_id,
                            nullopt,
                            message_dto.playlist_id);
        m_chat_message_rep.Insert(message);

        if (!message.GetId()) {
            throw CreateException();
        }
        return *message.GetId();
    }

    vector<MessageResponseDTO> ChatMessageUseCase::GetByUserId(uint32_t user_id,
                                                                optional<string> since_datetime) const {
        vector<ChatMessage> messages = m_chat_message_rep.FindByUserId(user_id,
                                                                       since_datetime);

        if (messages.empty()) {
            return {};
        }

        vector<MessageResponseDTO> messages_dto;
        messages_dto.reserve(messages.size());

        for (const ChatMessage& message : messages) {
            if (!message.GetId()) {
                throw NullPointerException();
            }
            optional<PlaylistResponseDTO> playlist_dto = GetPlaylist(message.GetPlaylistId());
            messages_dto.emplace_back(*message.GetId(),
                                      message.GetChatId(),
                                      message.GetSenderId(),
                                      message.GetContent(),
                                      message.GetDatetime(),
                                      playlist_dto);
        }

        return messages_dto;
    }

    vector<MessageResponseDTO> ChatMessageUseCase::GetUserMessages(uint32_t user_id,
                                                                   uint32_t chat_id) const {
        optional<bool> check_result = CheckAccess(chat_id, user_id);
        if (!check_result) {
            return {};
        }
        if (!*check_result) {
            throw AccessException();
        }

        vector<ChatMessage> messages = m_chat_message_rep.FindByChatId(chat_id);

        if (messages.empty()) {
            return {};
        }

        vector<MessageResponseDTO> messages_dto;
        messages_dto.reserve(messages.size());

        for (const ChatMessage& message : messages) {
            if (!message.GetId()) {
                throw NullPointerException();
            }
            optional<PlaylistResponseDTO> playlist_dto = GetPlaylist(message.GetPlaylistId());
            messages_dto.emplace_back(*message.GetId(),
                                      message.GetChatId(),
                                      message.GetSenderId(),
                                      message.GetContent(),
                                      message.GetDatetime(),
                                      playlist_dto);
        }

        return messages_dto;
    }

    optional<bool> ChatMessageUseCase::CheckAccess(uint32_t chat_id,
                                                   uint32_t user_id) const {
        optional<Chat> chat = m_chat_rep.Find(chat_id);
        if (!chat) {
            return {};
        }

        pair<uint32_t, uint32_t> user_ids = chat->GetUserIds();
        if (user_id != user_ids.first && user_id != user_ids.second) {
            return false;
        }

        return true;
    }

    optional<PlaylistResponseDTO> ChatMessageUseCase::GetPlaylist(optional<uint32_t> playlist_id) const {
        if (!playlist_id) {
            return nullopt;
        }

        return m_playlist_usecase.GetById(*playlist_id);
    }

}  // namespace music_share
