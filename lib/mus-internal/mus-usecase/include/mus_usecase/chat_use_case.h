#ifndef MUS_INTERNAL_MUS_USECASE_CHAT_USE_CASE_H_
#define MUS_INTERNAL_MUS_USECASE_CHAT_USE_CASE_H_

#include "mus-iusecase/ichat_use_case.h"
#include "mus-irepo/ichat_message_reprositoriy.h"
#include "mus-irepo/ichat_repository.h"

class ChatUseCase : public IChatUseCase {
public:
    ChatUseCase() = delete;

    ChatUseCase(const music_share::IChatReprository& chat_rep,
                const music_share::IChatMessageRepository& chat_message_rep);

    ChatUseCase(const ChatUseCase& chat_use_case);

    ChatUseCase& operator=(const ChatUseCase& chat_use_case);

    std::optional<uint32_t> Create(ChatRequestDTO chat) override;

    bool SendMessage(MessageRequestDTO message, uint32_t chat_id,
                     uint32_t user_id) override;

    std::vector<MessageResponseDTO> GetUserMessages(uint32_t user_id,
                                                    uint32_t chat_id) override;

    std::vector<ChatResponseDTO> GetByIdOfOneUser(uint32_t id) override;

    std::optional<ChatResponseDTO> GetByIdOfTwoUser(uint32_t first_id,
                                                    uint32_t second_id) override;

    ~ChatUseCase();

private:
    music_share::IChatReprository& m_chat_rep;
    music_share::IChatMessageRepository& m_chat_message_rep;

};

#endif  // MUS_INTERNAL_MUS_USECASE_CHAT_USE_CASE_H_
