#include "mus-controller/usercontroller.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>  // std::shared_ptr
#include <string>  // std::string
#include <cstdint>  // uint32_t
#include <optional>  // std::optional

#include "mus-iusecase/iuser_use_case.h"
#include "mus-irepo/iuser_repository.h"
#include "mus-dto/user_request_dto.h"
#include "mus-dto/user_response_dto.h"

using namespace testing;
using namespace music_share;

class MockUserUseCase : public IUserUseCase {
public:
    MOCK_METHOD1(Create, std::optional<uint32_t>(UserRequestDTO));
    MOCK_METHOD2(Update, std::optional<UserResponseDTO>(uint32_t, UserRequestDTO));
    MOCK_METHOD1(GetUserByUsername, std::optional<UserResponseDTO>(std::string));
    MOCK_METHOD1(GetUserByNickname, std::optional<UserResponseDTO>(std::string));
    MOCK_METHOD1(GetUserByID, std::optional<UserResponseDTO>(uint32_t));
};

TEST(USER_CONTROLLER, GET_USER_BY_NICKNAME) {
    auto usecase = std::make_shared<MockUserUseCase>();
    UserController::Request request = {
        .method = UserController::Request::Method::GET,
    };
    UserController controller(usecase);

    EXPECT_CALL(usecase, GetUserByNickname("")).Times(AtLeast(1));

    (void)controller.User(request);
}

TEST(USER_CONTROLLER, CREATE_USER) {
    auto usecase = std::make_shared<MockUserUseCase>();
    auto user_request_body = UserRequestDTO("", "", "", "");
    UserController::Request request = {
        .method = UserController::Request::Method::POST,
        .body = user_request_body
    };
    UserController controller(usecase);

    EXPECT_CALL(usecase, Create(user_request_body)).Times(AtLeast(1));

    (void)controller.User(request);
}

TEST(USER_CONTROLLER, GET_USER_BY_ID) {
    auto usecase = std::make_shared<MockUserUseCase>();
    UserController::Request request = {
        .method = UserController::Request::Method::GET,
    };
    UserController controller(usecase);

    EXPECT_CALL(usecase, GetUserByID(0)).Times(AtLeast(1));

    (void)controller.UserID(request);
}

TEST(USER_CONTROLLER, UPDATE_USER) {
    auto usecase = std::make_shared<MockUserUseCase>();
    auto user_request_body = UserRequestDTO("", "", "", "");
    UserController::Request request = {
        .method = UserController::Request::Method::POST,
        .body = user_request_body
    };
    UserController controller(usecase);

    EXPECT_CALL(usecase, Update(0, user_request_body)).Times(AtLeast(1));

    (void)controller.UserID(request);
}
