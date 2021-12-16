#ifndef MUS_INTERNAL_MUS_USECASE_CHAT_USE_CASE_H_
#define MUS_INTERNAL_MUS_USECASE_CHAT_USE_CASE_H_

#include <vector>

#include "mus-iusecase/ichat_use_case.h"
#include "mus-irepo/ichat_repository.h"

namespace music_share {

    class ChatUseCase : public IChatUseCase {
    public:
        ChatUseCase() = delete;

        explicit ChatUseCase(IChatRepository &chat_rep);

        ChatUseCase(const ChatUseCase &chat_use_case);

        ChatUseCase &operator=(const ChatUseCase &chat_use_case);

        uint32_t Create(uint32_t user_id,
                        const ChatRequestDTO& chat) override;

        std::vector<ChatResponseDTO> GetByIdOfOneUser(uint32_t id) const override;

        ChatResponseDTO GetByIdOfTwoUser(uint32_t first_id,
                                         uint32_t second_id) const override;

        ~ChatUseCase() = default;

    private:
        IChatRepository &m_chat_rep;
    };

}  // namespace music_share

#endif  // MUS_INTERNAL_MUS_USECASE_CHAT_USE_CASE_H_
