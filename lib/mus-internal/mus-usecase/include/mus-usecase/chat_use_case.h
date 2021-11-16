#ifndef MUS_INTERNAL_MUS_USECASE_CHAT_USE_CASE_H_
#define MUS_INTERNAL_MUS_USECASE_CHAT_USE_CASE_H_

#include "ichat_use_case.h"
#include "ichat_message_reprositoriy.h"
#include "ichat_reprositoriy.h"

class ChatUseCase : IChatUseCase {
public:
    ChatUseCase() = delete;

    ChatUseCase(const IChatReprositoriy& chat_rep,
                const IChatMessageRepositoriy& chat_message_rep);

    ChatUseCase(const ChatUseCase& chat_use_case) = default;

    ChatUseCase& operator=(const ChatUseCase& chat_use_case) = default;

    bool Create(ChatRequestDTO chat) override;

    bool SendMessage(MessageRequestDTO message, int id_chat,
                     int id_user) override;

    std::vector<MessageResponseDTO> GetUserMessages(int user_id,
                                                    int chat_id) override;

    std::vector<ChatResponseDTO> GetByIdOfOneUser(int id) override;

    std::optional<ChatResponseDTO> GetByIdOfTwoUser(int first_id,
                                                    int second_id) override;

    ~ChatUseCase();

private:
    IChatReprositoriy& m_chat_rep;
    IChatMessageRepositoriy m_chat_message_rep;

};

#endif  // MUS_INTERNAL_MUS_USECASE_CHAT_USE_CASE_H_
