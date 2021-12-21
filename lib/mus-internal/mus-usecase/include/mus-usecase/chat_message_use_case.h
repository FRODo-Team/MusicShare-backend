// Oweners: Darya Vlaskina, ML-13
#ifndef MUS_INTERNAL_MUS_USECASE_CHAT_MESSAGE_USE_CASE_H_
#define MUS_INTERNAL_MUS_USECASE_CHAT_MESSAGE_USE_CASE_H_

#include <optional>
#include <string>
#include <vector>

#include "mus-iusecase/ichat_message_use_case.h"
#include "mus-irepo/ichat_message_repository.h"

namespace music_share {

    class ChatMessageUseCase : public IChatMessageUseCase {
    public:
        ChatMessageUseCase() = delete;

        ChatMessageUseCase(IChatMessageRepository& chat_message_rep);

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
        IChatMessageRepository &m_chat_message_rep;
    };

}  // namespace music_share

#endif  // MUS_INTERNAL_MUS_USECASE_CHAT_MESSAGE_USE_CASE_H_
