#include "mus-delivery/handler/chatmessagehandler.h"

#include <cstring>
#include <ranges>

#include "http/server/router.h"
#include "http/common.h"
#include "serializer.h"

namespace music_share::delivery {

void ChatMessageHandler::Config(http::server::router::Router& router) {
    std::string prefix = "/api/v1/chats/:chat_id([0-9]+)/messages";

    router.GET(http::server::router::Route(
        prefix,
        [this](auto, auto params) {
            auto body = GetUserMessages(1, atoi(params["chat_id"].c_str()));

            http::common::Response response;
            response.set(http::common::header::content_type,
                         "application/json");
            response.body() = nlohmann::json(body).dump();
            return response;
        }
    ));

    router.POST(http::server::router::Route(
        prefix,
        [this](http::common::Request request, auto params) {
            (void)SendMessage(
                nlohmann::json::parse(request.body())
                    .template get<MessageRequestDTO>(),
                atoi(params["chat_id"].c_str()),
                1
            );

            http::common::Response response;
            return response;
        }
    ));
}

uint32_t
ChatMessageHandler::SendMessage(const MessageRequestDTO& message,
                              uint32_t chat_id, uint32_t user_id) {
    return chat_id;
}

std::vector<MessageResponseDTO>
ChatMessageHandler::GetUserMessages(uint32_t user_id,
                                    uint32_t chat_id) {
    return {MessageResponseDTO(1, chat_id, user_id, "hi duuude", "dome date")};
}

}  // namespace music_share::delivery
