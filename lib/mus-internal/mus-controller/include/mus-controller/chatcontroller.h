#ifndef MUS_MUSINTERNAL_MUSCONTROLLER_ChatCONTROLLER_H_
#define MUS_MUSINTERNAL_MUSCONTROLLER_ChatCONTROLLER_H_

#include "mus-controller/endpoint.h"

#include <memory>  // std::shared_ptr

#include "mus-dto/chat_request_dto.h"  // music_share::ChatRequestDTO
#include "mus-dto/chat_response_dto.h"  // music_share::ChatRequestDTO
#include "mus-usecase/chat_use_case.h"  // music_share::ChatUseCase
#include "mus-controller/request.h"
#include "mus-controller/response.h"

namespace music_share {

class ChatController {
public:
    using Request = Request<ChatRequestDTO>;
    using Response = Response<ChatResponseDTO>;

    ChatController();
    ~ChatController() = default;

    Response Chat(const Request& response) {
        return m_chat_endpoint(response);
    }
    Response ChatIDMessage(const Request& response) {
        return m_chat_id_message_endpoint(response);
    }
private:
    class ChatEndpoint : public Endpoint<Request, Response> {
    public:
        ChatEndpoint(std::shared_ptr<IChatUseCase> chat_usecase);

        virtual Response Get(const Request& request) {
            return Response();
        }
        virtual Response Post(const Request& request) {
            return Response();
        }
    private:
        std::shared_ptr<IChatUseCase> m_chat_usecase;
    };

    class ChatIDMessageEndpoint : public Endpoint<Request, Response> {
    public:
        ChatIDMessageEndpoint(std::shared_ptr<IChatUseCase> chat_usecase);

        virtual Response Get(const Request& request) {
            return Response();
        }
        virtual Response Post(const Request& request) {
            return Response();
        }
    private:
        std::shared_ptr<IChatUseCase> m_chat_usecase;
    };

    std::shared_ptr<IChatUseCase> m_chat_usecase;
    ChatEndpoint m_chat_endpoint;
    ChatIDMessageEndpoint m_chat_id_message_endpoint;
};

}  // namespace music_share

#endif  // MUS_MUSINTERNAL_MUSCONTROLLER_ChatCONTROLLER_H_
