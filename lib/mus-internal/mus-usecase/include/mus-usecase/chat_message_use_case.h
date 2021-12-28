// Oweners: Darya Vlaskina, ML-13
#ifndef MUS_INTERNAL_MUS_USECASE_CHAT_MESSAGE_USE_CASE_H_
#define MUS_INTERNAL_MUS_USECASE_CHAT_MESSAGE_USE_CASE_H_

#include <optional>
#include <string>
#include <vector>

#include "mus-iusecase/ichat_message_use_case.h"
#include "mus-iusecase/iplaylist_use_case.h"
#include "mus-irepo/ichat_message_repository.h"
#include "mus-irepo/ichat_repository.h"

namespace music_share {

    class ChatMessageUseCase : public IChatMessageUseCase {
    public:
        ChatMessageUseCase() = delete;

        ChatMessageUseCase(IChatMessageRepository& chat_message_rep,
                           IChatRepository& chat_rep,
                           IPlaylistUseCase& playlist_usecase);

        ChatMessageUseCase(const ChatMessageUseCase& chat_message_use_case);

        ChatMessageUseCase& operator=(const ChatMessageUseCase& chat_message_use_case);

        uint32_t SendMessage(const MessageRequestDTO& message_dto, uint32_t chat_id,
                             uint32_t user_id,
                             std::optional<std::string> datetime) override;

        std::vector<MessageResponseDTO> GetUserMessages(uint32_t user_id,
                                                        uint32_t chat_id) const override;

        std::vector<MessageResponseDTO> GetByUserId(uint32_t user_id,
                                                    std::optional<std::string> since_datetime) const override;

        ~ChatMessageUseCase() = default;

    private:
        std::optional<bool> CheckAccess(uint32_t chat_id, uint32_t user_id) const;
        std::optional<PlaylistResponseDTO> GetPlaylist(std::optional<uint32_t> playlist_id) const;

        IChatMessageRepository& m_chat_message_rep;
        IChatRepository& m_chat_rep;
        IPlaylistUseCase& m_playlist_usecase;
    };

}  // namespace music_share

#endif  // MUS_INTERNAL_MUS_USECASE_CHAT_MESSAGE_USE_CASE_H_
