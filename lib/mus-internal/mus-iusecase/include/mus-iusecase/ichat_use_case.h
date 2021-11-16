#ifndef MUS_INTERNAL_MUS_IUSECASE_ICHAT_USE_CASE_H_
#define MUS_INTERNAL_MUS_IUSECASE_ICHAT_USE_CASE_H_

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

    virtual bool SendMessage(MessageRequestDTO message, int id_chat,
                             int id_user) = 0;

    virtual std::vector<MessageResponseDTO> GetUserMessages(int user_id,
                                                            int chat_id) = 0;

    virtual std::vector<ChatResponseDTO> GetByIdOfOneUser(int id) = 0;

    virtual std::optional<ChatResponseDTO> GetByIdOfTwoUser(int first_id, int second_id) = 0;

    virtual ~IChatUseCase() {};
};

#endif  // MUS_INTERNAL_MUS_IUSECASE_ICHAT_USE_CASE_H_
