#ifndef MUS_INTERNAL_MUS_IUSECASE_ICHAT_USE_CASE_H_
#define MUS_INTERNAL_MUS_IUSECASE_ICHAT_USE_CASE_H_

#include <string>
#include <vector>

#include "mus-dto/chat_request_dto.h"
#include "mus-dto/chat_response_dto.h"

namespace music_share {

class IChatUseCase {
public:
    IChatUseCase() = default;

    IChatUseCase(const IChatUseCase& chat_use_case) = default;

    IChatUseCase& operator=(const IChatUseCase& chat_use_case) = default;

    virtual uint32_t Create(uint32_t user_id,
                            const ChatRequestDTO& chat) = 0;

    virtual std::vector<ChatResponseDTO> GetByIdOfOneUser(uint32_t id) = 0 const;

    virtual ChatResponseDTO GetByIdOfTwoUser(uint32_t first_id,
                                             uint32_t second_id) = 0 const;

    virtual ~IChatUseCase() = default;
};

} // namespace music_share

#endif  // MUS_INTERNAL_MUS_IUSECASE_ICHAT_USE_CASE_H_
