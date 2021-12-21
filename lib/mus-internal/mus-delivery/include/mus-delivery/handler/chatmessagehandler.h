#ifndef MUS_MUSINTERNAL_MUSDELIVERY_HANDLER_CHATMESSAGEHANDLER_H_
#define MUS_MUSINTERNAL_MUSDELIVERY_HANDLER_CHATMESSAGEHANDLER_H_

#include <memory>  // std::shared_ptr
#include <optional>  // std::optional
#include <vector>  // std::vector

#include "mus-iusecase/ichat_message_use_case.h"
#include "http/server/router/router.h"

namespace music_share::delivery {

class ChatMessageHandler final {
public:
    ChatMessageHandler(IChatMessageUseCase& usecase);
    void Config(http::server::router::Router& router);

    uint32_t
    SendMessage(const MessageRequestDTO& message,
                uint32_t chat_id, uint32_t user_id);

    std::vector<MessageResponseDTO>
    GetUserMessages(uint32_t user_id,
                    uint32_t chat_id);

    std::vector<MessageResponseDTO>
    GetMessagesByUser(uint32_t user_id, std::optional<std::string> since_date);
private:
    [[maybe_unused]] IChatMessageUseCase& m_usecase;
};

}  // namespace music_share::delivery

#endif  // MUS_MUSINTERNAL_MUSDELIVERY_HANDLER_CHATMESSAGEHANDLER_H_
