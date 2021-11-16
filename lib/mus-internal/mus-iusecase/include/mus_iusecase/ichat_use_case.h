#ifndef MUS_INTERNAL_MUS_IUSECASE_ICHAT_USE_CASE_H_
#define MUS_INTERNAL_MUS_IUSECASE_ICHAT_USE_CASE_H_

#include <cstdint>
#include <string>
#include <vector>

#include "chat_request_dto.h"
#include "chat_response_dto.h"
#include "message_response_dto.h"
#include "message_request_dto.h"

class IChatUseCase {
public:
    IChatUseCase() = default;

    IChatUseCase(const IChatUseCase& chat_use_case) = default;

    IChatUseCase& operator=(const IChatUseCase& chat_use_case) = default;

    virtual bool Create(ChatRequestDTO chat) = 0;

    virtual bool SendMessage(MessageRequestDTO message, uint32_t id_chat,
                             uint32_t id_user) = 0;

    virtual std::vector<MessageResponseDTO> GetUserMessages(uint32_t user_id,
                                                            uint32_t chat_id) = 0;

    virtual std::vector<ChatResponseDTO> GetByIdOfOneUser(uint32_t id) = 0;

    virtual std::optional<ChatResponseDTO> GetByIdOfTwoUser(uint32_t first_id,
                                                            uint32_t second_id) = 0;

    virtual ~IChatUseCase() {};
};

#endif  // MUS_INTERNAL_MUS_IUSECASE_ICHAT_USE_CASE_H_
