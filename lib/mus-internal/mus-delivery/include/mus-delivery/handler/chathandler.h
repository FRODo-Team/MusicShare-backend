#ifndef MUS_MUSINTERNAL_MUSDELIVERY_HANDLER_CHATHANDLER_H_
#define MUS_MUSINTERNAL_MUSDELIVERY_HANDLER_CHATHANDLER_H_

#include <memory>  // std::shared_ptr
#include <vector>  // std::vector
#include <optional>  // std::optional

#include "mus-iusecase/ichat_use_case.h"
#include "http/server/router/router.h"

namespace music_share::delivery {

class ChatHandler final {
public:
    //ChatHandler(IChatUseCase& usecase);
    ChatHandler() = default;
    void Config(http::server::router::Router& router);

    uint32_t
    Create(uint32_t user_id, const ChatRequestDTO& chat);

    std::vector<ChatResponseDTO>
    GetAll(std::optional<uint32_t> companion_id = std::nullopt);
private:
    //[[maybe_unused]] IChatUseCase& m_usecase;
};

}  // namespace music_share::delivery

#endif  // MUS_MUSINTERNAL_MUSDELIVERY_HANDLER_CHATHANDLER_H_
