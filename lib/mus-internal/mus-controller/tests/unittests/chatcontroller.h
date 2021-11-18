#include "mus-controller/chatcontroller.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>  // std::shared_ptr
#include <string>  // std::string
#include <vector>  // std::vector
#include <cstdint>  // uint32_t
#include <optional>  // std::optional

#include "mus-iusecase/ichat_use_case.h"
#include "mus-irepo/ichat_repository.h"
#include "mus-dto/chat_request_dto.h"
#include "mus-dto/chat_response_dto.h"
#include "mus-dto/message_request_dto.h"
#include "mus-dto/message_response_dto.h"

using namespace testing;
using namespace music_share;

class MockChatUseCase : public IChatUseCase {
public:
    MOCK_METHOD2(Create, std::optional<uint32_t>(uint32_t, ChatRequestDTO));
    MOCK_METHOD3(SendMessage, bool(MessageRequestDTO, uint32_t, uint32_t));
    MOCK_METHOD2(GetUserMessages,
                 std::optional<MessageResponseDTO>(uint32_t, uint32_t));
    MOCK_METHOD1(GetByIdOfOneUser, std::vector<ChatResponseDTO>(uint32_t));
    MOCK_METHOD2(GetByIdOfTwoUser, std::optional<ChatResponseDTO>(uint32_t, uint32_t));
};

TEST(CHAT_CONTROLLER, CREATE) {
    auto usecase = std::make_shared<MockChatUseCase>();
    auto body = ChatRequestDTO(0);
    ChatController::Request request = {
        .method = ChatController::Request::Method::POST,
        .body = body
    };
    ChatController controller(usecase);

    EXPECT_CALL(usecase, Create(0, body)).Times(AtLeast(1));

    (void)controller.Chat(request);
}

TEST(CHAT_CONTROLLER, GET_BY_ID_OF_ONE_USER) {
    auto usecase = std::make_shared<MockChatUseCase>();
    ChatController::Request request = {
        .method = ChatController::Request::Method::GET,
    };
    ChatController controller(usecase);

    EXPECT_CALL(usecase, GetByIdOfOneUser(0)).Times(AtLeast(1));

    (void)controller.Chat(request);
}

TEST(CHAT_CONTROLLER, GET_BY_ID_OF_TWO_USER) {
    auto usecase = std::make_shared<MockChatUseCase>();
    ChatController::Request request = {
        .method = ChatController::Request::Method::GET,
    };
    ChatController controller(usecase);

    EXPECT_CALL(usecase, GetByIdOfTwoUser(0, 1)).Times(AtLeast(1));

    (void)controller.Chat(request);
}
