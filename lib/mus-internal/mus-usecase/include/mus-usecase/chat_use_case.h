// Oweners: Darya Vlaskina, ML-13
#ifndef MUS_INTERNAL_MUS_USECASE_CHAT_USE_CASE_H_
#define MUS_INTERNAL_MUS_USECASE_CHAT_USE_CASE_H_

#include <vector>

#include "mus-iusecase/ichat_use_case.h"
#include "mus-irepo/ichat_repository.h"
#include "mus-iusecase/iuser_use_case.h"

namespace music_share {

    class ChatUseCase : public IChatUseCase {
    public:
        ChatUseCase() = delete;

        explicit ChatUseCase(IChatRepository &chat_rep,
                             IUserUseCase &user_usecase);

        ChatUseCase(const ChatUseCase &chat_use_case);

        ChatUseCase &operator=(const ChatUseCase &chat_use_case);

        uint32_t Create(uint32_t user_id,
                        const ChatRequestDTO& chat) override;

        std::vector<ChatResponseDTO> GetByIdOfOneUser(uint32_t id) const override;

        ChatResponseDTO GetByIdOfTwoUser(uint32_t first_id,
                                         uint32_t second_id) const override;

        ~ChatUseCase() = default;

    private:
        std::pair<std::string, std::string> GetUsersNicknames(uint32_t user_first_id,
                                                              uint32_t user_second_id) const;

        IChatRepository &m_chat_rep;
        IUserUseCase &m_user_usecase;
    };

}  // namespace music_share

#endif  // MUS_INTERNAL_MUS_USECASE_CHAT_USE_CASE_H_
