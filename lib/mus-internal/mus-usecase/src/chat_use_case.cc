// Oweners: Darya Vlaskina, ML-13
#include "mus-usecase/chat_use_case.h"

#include <memory>
#include <optional>

#include "mus-usecase/exception/access_exception.h"
#include "mus-usecase/exception/create_exception.h"
#include "mus-usecase/exception/exist_exception.h"
#include "mus-usecase/exception/invalid_data_exception.h"
#include "mus-usecase/exception/null_pointer_exception.h"

using std::make_pair;
using std::make_unique;
using std::nullopt;
using std::optional;
using std::vector;
using std::pair;
using std::string;

namespace music_share {

    ChatUseCase::ChatUseCase(IChatRepository &chat_rep,
                             IUserUseCase &user_usecase)
                            : m_chat_rep(chat_rep),
                            m_user_usecase(user_usecase) { }

    ChatUseCase::ChatUseCase(const ChatUseCase &chat_use_case)
                            : m_chat_rep(chat_use_case.m_chat_rep),
                              m_user_usecase(chat_use_case.m_user_usecase){ }

    ChatUseCase& ChatUseCase::operator=(const ChatUseCase &chat_use_case) {
        m_chat_rep = chat_use_case.m_chat_rep;
        m_user_usecase = chat_use_case.m_user_usecase;
        return *this;
    }

    uint32_t ChatUseCase::Create(uint32_t user_id,
                                 const ChatRequestDTO& chat_request_dto) {
        optional<Chat> chat_exist = m_chat_rep.FindByIdsOfUserPair(user_id,
                                                         chat_request_dto.target_id);
        if (chat_exist) {
            throw ExistException();
        }

        Chat chat(user_id,
                chat_request_dto.target_id);

        m_chat_rep.Insert(chat);

        if (!chat.GetId()) {
            throw CreateException();
        }
        return *chat.GetId();
    }

    vector<ChatResponseDTO> ChatUseCase::GetByIdOfOneUser(uint32_t id) const {
        vector<Chat> chats = m_chat_rep.FindByUserId(id);

        if (chats.empty()) {
            return {};
        }

        vector<ChatResponseDTO> chats_dto;
        chats_dto.reserve(chats.size());
        for (const Chat& chat: chats) {
            if (!chat.GetId()) {
                throw NullPointerException();
            }
            pair<string, string> nicknames = GetUsersNicknames(chat.GetUserIds().first,
                                                      chat.GetUserIds().second);
            chats_dto.emplace_back(*chat.GetId(),
                                chat.GetUserIds().first,
                                chat.GetUserIds().second,
                                nicknames);
        }

        return chats_dto;
    }

    ChatResponseDTO ChatUseCase::GetByIdOfTwoUser(uint32_t first_id,
                                                  uint32_t second_id) const {
        optional<Chat> chat = m_chat_rep.FindByIdsOfUserPair(first_id,
                                                             second_id);

        if (!chat) {
            throw InvalidDataException();
        }

        pair<string, string> nicknames = GetUsersNicknames( chat->GetUserIds().first,
                                                            chat->GetUserIds().second);
        return ChatResponseDTO(*chat->GetId(),
                               chat->GetUserIds().first,
                               chat->GetUserIds().second,
                               nicknames);
    }

    pair<string, string> ChatUseCase::GetUsersNicknames(uint32_t user_first_id,
                                                        uint32_t user_second_id) const {
        UserResponseDTO user_first = m_user_usecase.GetById(user_first_id);
        UserResponseDTO user_second = m_user_usecase.GetById(user_second_id);

        return make_pair(user_first.nickname,
                        user_second.nickname);
    }

}  // namespace music_share
