// Oweners: Darya Vlaskina, ML-13
#ifndef MUS_INTERNAL_MUS_IUSECASE_ICHAT_MESSAGE_USE_CASE_H_
#define MUS_INTERNAL_MUS_IUSECASE_ICHAT_MESSAGE_USE_CASE_H_

#include <vector>
#include <optional>

#include "mus-dto/message_request_dto.h"
#include "mus-dto/message_response_dto.h"

namespace music_share {

    class IChatMessageUseCase {
    public:
        IChatMessageUseCase() = default;

        IChatMessageUseCase(const IChatMessageUseCase &chat_message_use_case) = default;

        IChatMessageUseCase &operator=(const IChatMessageUseCase &chat_message_use_case) = default;

        virtual uint32_t SendMessage(const MessageRequestDTO& message_dto,
                                     uint32_t chat_id, uint32_t user_id,
                                     std::optional<std::string> datetime = std::nullopt) = 0;

        virtual std::vector<MessageResponseDTO> GetUserMessages(uint32_t user_id,
                                                                uint32_t chat_id) const = 0;

        virtual std::vector<MessageResponseDTO> GetByUserId(uint32_t user_id,
                                                            std::optional<std::string> since_datetime) const = 0;

        virtual ~IChatMessageUseCase() = default;
    };

}

#endif  // MUS_INTERNAL_MUS_IUSECASE_ICHAT_MESSAGE_USE_CASE_H_
