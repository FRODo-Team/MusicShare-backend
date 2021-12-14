#include "mus-usecase/chat_use_case.h"

#include <memory>
#include <optional>

#include "mus-usecase/exception/access_exception.h"
#include "mus-usecase/exception/create_exception.h"
#include "mus-usecase/exception/invalid_data_exception.h"
#include "mus-usecase/exception/null_pointer_exception.h"

using std::make_pair;
using std::make_unique;
using std::nullopt;
using std::optional;
using std::vector;

namespace music_share {

    ChatUseCase::ChatUseCase(IChatRepository &chat_rep)
                            : m_chat_rep(chat_rep) { }

    ChatUseCase::ChatUseCase(const ChatUseCase &chat_use_case)
                            : m_chat_rep(chat_use_case.m_chat_rep) { }

    ChatUseCase& ChatUseCase::operator=(const ChatUseCase &chat_use_case) {
        m_chat_rep = chat_use_case.m_chat_rep;
        return *this;
    }

    uint32_t ChatUseCase::Create(uint32_t user_id,
                                 const ChatRequestDTO& chat_request_dto) {
        auto chat = make_unique<Chat>(user_id,
                                                    chat_request_dto.target_id);

        m_chat_rep.Insert(*chat);

        if (!chat->GetId()) {
            throw CreateException();
        }

        return *chat->GetId();
    }

    ChatResponseDTO ChatUseCase::GetById(uint32_t id) {
        optional<Chat> chat = m_chat_rep.Find(id);

        if (!chat) {
            throw InvalidDataException();
        }
        if (!chat->GetId()) {
            throw NullPointerException();
        }

        return ChatResponseDTO(*chat->GetId(),
                               chat->GetUserIds().first,
                               chat->GetUserIds().second);
    }

    void ChatUseCase::Delete(uint32_t user_id, uint32_t chat_id) {
        optional<Chat> chat = m_chat_rep.Find(chat_id);

        if (!chat) {
            throw InvalidDataException();
        }
        if (chat->GetUserIds().first != user_id
            && chat->GetUserIds().second != user_id) {
            throw AccessException();
        }

        m_chat_rep.Delete(*chat);
    }

    vector<ChatResponseDTO> ChatUseCase::GetByIdOfOneUser(uint32_t id) {
        vector<Chat> chats = m_chat_rep.FindByUserId(id);

        if (chats.empty()) {
            throw InvalidDataException();
        }

        vector<ChatResponseDTO> chats_dto;
        chats_dto.reserve(chats.size());
        for (const Chat& chat: chats) {
            if (!chat.GetId()) {
                throw NullPointerException();
            }
            chats_dto.emplace_back(*chat.GetId(),
                                chat.GetUserIds().first,
                                chat.GetUserIds().second);
        }

        return chats_dto;
    }

    ChatResponseDTO ChatUseCase::GetByIdOfTwoUser(uint32_t first_id,
                                                  uint32_t second_id) {
        Chat chat = m_chat_rep.FindByIdsOfUserPair(first_id, second_id);

        if (!chat.GetId()) {
            throw InvalidDataException();
        }

        return ChatResponseDTO(*chat.GetId(),
                               chat.GetUserIds().first,
                               chat.GetUserIds().second);
    }

}  // namespace music_share
