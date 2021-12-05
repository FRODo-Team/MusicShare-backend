#ifndef MUS_INTERNAL_MUS_IUSECASE_ICHAT_MESSAGE_USE_CASE_H_
#define MUS_INTERNAL_MUS_IUSECASE_ICHAT_MESSAGE_USE_CASE_H_

#include <vector>

#include "mus-dto/message_request_dto.h"
#include "mus-dto/message_response_dto.h"

namespace music_share {

    class IChatMessageUseCase {
    public:
        IChatMessageUseCase() = default;

        IChatMessageUseCase(const IChatMessageUseCase &chat_message_use_case) = default;

        IChatMessageUseCase &operator=(const IChatMessageUseCase &chat_message_use_case) = default;

        virtual uint32_t SendMessage(const MessageRequestDTO& message,
                                     const std::string& datetime,
                                     uint32_t chat_id, uint32_t user_id) = 0;

        virtual std::vector<MessageResponseDTO> GetUserMessages(uint32_t user_id,
                                                                uint32_t chat_id) = 0;

        virtual MessageResponseDTO FindById(uint32_t id) = 0;

        virtual void Delete(uint32_t user_id, uint32_t message_id) = 0;

        virtual MessageResponseDTO Update(uint32_t user_id,
                                          uint32_t message_id) = 0;

        virtual ~IChatMessageUseCase() = default;
    };

}

#endif  // MUS_INTERNAL_MUS_IUSECASE_ICHAT_MESSAGE_USE_CASE_H_
