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

        uint32_t SendMessage(const MessageRequestDTO& message, const std::string& datetime,
                         uint32_t chat_id, uint32_t user_id) override;

        std::vector<MessageResponseDTO> GetUserMessages(uint32_t user_id,
                                                        uint32_t chat_id) override;

        MessageResponseDTO FindById(uint32_t id) override;

        void Delete(uint32_t user_id, uint32_t message_id) override;

        MessageResponseDTO Update(uint32_t user_id,
                                  uint32_t message_id) override;

        ~ChatMessageUseCase() = default;

    private:
        IChatMessageRepository &m_chat_message_rep;
    };

}  // namespace music_share

#endif  // MUS_INTERNAL_MUS_USECASE_CHAT_MESSAGE_USE_CASE_H_
