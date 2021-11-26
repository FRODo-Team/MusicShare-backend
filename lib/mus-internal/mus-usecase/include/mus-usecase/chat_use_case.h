#ifndef MUS_INTERNAL_MUS_USECASE_CHAT_USE_CASE_H_
#define MUS_INTERNAL_MUS_USECASE_CHAT_USE_CASE_H_

#include "mus-iusecase/ichat_use_case.h"
#include "mus-irepo/ichat_repository.h"

namespace music_share {

class ChatUseCase : public IChatUseCase {
public:
    ChatUseCase() = delete;

    ChatUseCase(const IChatRepository &chat_rep);

    ChatUseCase(const ChatUseCase &chat_use_case);

    ChatUseCase &operator=(const ChatUseCase &chat_use_case);

    std::optional <uint32_t> Create(ChatRequestDTO chat) override;

    std::vector <ChatResponseDTO> GetByIdOfOneUser(uint32_t id) override;

    std::optional <ChatResponseDTO> GetByIdOfTwoUser(uint32_t first_id,
                                                     uint32_t second_id) override;

    ~ChatUseCase();

private:
    IChatRepository &m_chat_rep;
};

} // namespace music_share

#endif  // MUS_INTERNAL_MUS_USECASE_CHAT_USE_CASE_H_
