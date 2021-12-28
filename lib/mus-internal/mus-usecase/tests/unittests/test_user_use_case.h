// Oweners: Darya Vlaskina, ML-13
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <vector>
#include <string>
#include <utility>

#include "mus-iusecase/iuser_use_case.h"
#include "mus-irepo/iuser_repository.h"
#include "mus-usecase/user_use_case.h"
#include "mus-dto/user_request_dto.h"
#include "mus-usecase/exception/create_exception.h"
#include "mus-usecase/exception/exist_exception.h"
#include "mus-usecase/exception/invalid_data_exception.h"
#include "mus-usecase/exception/null_pointer_exception.h"
#include "matcher/nullopt_matcher.h"
#include "mock/mock_user_repository.h"

using ::testing::AtLeast;
using testing::Invoke;
using testing::Return;

using std::make_shared;
using std::nullopt;
using std::optional;
using std::shared_ptr;
using std::string;
using std::vector;

using music_share::CreateException;
using music_share::ExistException;
using music_share::InvalidDataException;
using music_share::NullPointerException;
using music_share::IUserRepository;
using music_share::User;
using music_share::UserUseCase;

MATCHER_P(UserEqualement, other, "Equality matcher for type User") {
    return arg.GetUsername() == other.GetUsername();
}

class TestUserUseCase : public ::testing::Test {
protected:
    void SetUp() {
        user_rep = make_shared<MockUserRepository>();
        user_usecase = make_shared<UserUseCase>(*user_rep);

        user = make_shared<User>("user", "user@mail.ru",
                                 "hash", "user",
                                 User::AccessLevel::Authorized,
                                 1);
        user_null = make_shared<User>("user", "user@mail.ru",
                                 "hash", "user",
                                 User::AccessLevel::Authorized,
                                 nullopt);

        user_request = make_shared<UserRequestDTO>("user", "hash",
                                        "user", "user@mail.ru");
    }

    void TearDown() { }

    shared_ptr<UserUseCase> user_usecase;
    shared_ptr<MockUserRepository> user_rep;
    shared_ptr<User> user;
    shared_ptr<User> user_null;
    shared_ptr<UserRequestDTO> user_request;
};

TEST_F(TestUserUseCase, CreateSuccess) {
    uint32_t id_expected = 1;

    EXPECT_CALL(*user_rep, FindByUsername(user_request->username))
            .Times(AtLeast(1));

    EXPECT_CALL(*user_rep, FindByEmail(user_request->email))
            .Times(AtLeast(1));

    EXPECT_CALL(*user_rep, Insert(UserEqualement(*user)))
                .WillOnce(Invoke([this](User& user_out) {
                    user_out = *this->user;
                }));

    EXPECT_EQ(user_usecase->Create(*user_request), id_expected);
}

TEST_F(TestUserUseCase, CreateException) {
    EXPECT_CALL(*user_rep, FindByUsername(user_request->username))
            .Times(AtLeast(1));

    EXPECT_CALL(*user_rep, FindByEmail(user_request->email))
            .Times(AtLeast(1));

    EXPECT_CALL(*user_rep, Insert(UserEqualement(*user)))
                                .Times(AtLeast(1));

    EXPECT_THROW(user_usecase->Create(*user_request), CreateException);
}

TEST_F(TestUserUseCase, CreateExistEmail) {
    user_request->username = "user2";

    EXPECT_CALL(*user_rep, FindByUsername(user_request->username))
            .Times(AtLeast(1));

    EXPECT_CALL(*user_rep, FindByEmail(user_request->email))
            .Times(AtLeast(1))
            .WillOnce(Return(*user));

    EXPECT_THROW(user_usecase->Create(*user_request), ExistException);
}

TEST_F(TestUserUseCase, CreateExistUsername) {
    EXPECT_CALL(*user_rep, FindByUsername(user_request->username))
            .WillOnce(Return(*user));

    EXPECT_THROW(user_usecase->Create(*user_request), ExistException);
}

TEST_F(TestUserUseCase, Update) {
    UserResponseDTO user_response_expected(1,
                                           "user",
                                           "user");

    EXPECT_CALL(*user_rep, Update(UserEqualement(*user)))
            .Times(AtLeast(1));

    UserResponseDTO user_response = user_usecase->Update(1, *user_request);

    EXPECT_EQ(user_response.id, user_response_expected.id);
    EXPECT_EQ(user_response.nickname, user_response_expected.nickname);
    EXPECT_EQ(user_response.username, user_response_expected.username);
}


TEST_F(TestUserUseCase, GetByUsernameSuccess) {
    UserResponseDTO user_response_expected(1,
                                           "user",
                                           "user");

    EXPECT_CALL(*user_rep, FindByUsername("user"))
            .WillOnce(Return(*user));

    UserResponseDTO user_response = user_usecase->GetByUsername("user");

    EXPECT_EQ(user_response.id, user_response_expected.id);
    EXPECT_EQ(user_response.nickname, user_response_expected.nickname);
    EXPECT_EQ(user_response.username, user_response_expected.username);
}

TEST_F(TestUserUseCase, GetByUsernameNotExist) {
    EXPECT_CALL(*user_rep, FindByUsername("user"))
            .WillOnce(Return(nullopt));

    EXPECT_THROW(user_usecase->GetByUsername("user"), InvalidDataException);
}

TEST_F(TestUserUseCase, GetByUsernameNullPointer) {
    EXPECT_CALL(*user_rep, FindByUsername("user"))
            .WillOnce(Return(*user_null));

    EXPECT_THROW(user_usecase->GetByUsername("user"), NullPointerException);
}

TEST_F(TestUserUseCase, GetByNicknamesSuccess) {
    UserResponseDTO user_response_expected(1,
                                           "user",
                                           "user");
    vector<User> users;
    users.emplace_back(*user);

    EXPECT_CALL(*user_rep, FindByNickname("user"))
            .WillOnce(Return(users));

    vector<string> nicknames;
    nicknames.emplace_back("user");

    vector<UserResponseDTO> user_response = user_usecase->GetByNicknames(nicknames);

    EXPECT_EQ(user_response[0].nickname, user_response_expected.nickname);
    EXPECT_EQ(user_response[0].username, user_response_expected.username);
    EXPECT_EQ(user_response[0].id, user_response_expected.id);
}

TEST_F(TestUserUseCase, GetByNicknamesNotExist) {
    vector<User> users;

    EXPECT_CALL(*user_rep, FindByNickname("user"))
            .WillOnce(Return(users));

    vector<string> nicknames;
    nicknames.emplace_back("user");

    vector<UserResponseDTO> users_response = user_usecase->GetByNicknames(nicknames);

    EXPECT_TRUE(users_response.empty());

}

TEST_F(TestUserUseCase, GetByNicknamesNullPointer) {
    vector<User> users;
    users.emplace_back(*user_null);

    EXPECT_CALL(*user_rep, FindByNickname("user"))
            .WillOnce(Return(users));

    vector<string> nicknames;
    nicknames.emplace_back("user");

    EXPECT_THROW(user_usecase->GetByNicknames(nicknames),
                 NullPointerException);
}

TEST_F(TestUserUseCase, GetByNicknamesEmptyRequest) {
    vector<UserResponseDTO> user_response_expected;
    user_response_expected.emplace_back(1, "user", "user");
    user_response_expected.emplace_back(2, "user2", "user2");
    vector<User> users;
    users.emplace_back(*user);
    users.emplace_back("user2", "user2@mail.ru",
                       "password", "user2",
                       music_share::User::AccessLevel::Authorized, 2);

    EXPECT_CALL(*user_rep, FetchAll(NulloptEqualement(nullopt)))
                .WillOnce(Return(users));

    vector<string> nicknames;

    vector<UserResponseDTO> user_response = user_usecase->GetByNicknames(nicknames);

    EXPECT_EQ(user_response[0].nickname, user_response_expected[0].nickname);
    EXPECT_EQ(user_response[0].username, user_response_expected[0].username);
    EXPECT_EQ(user_response[0].id, user_response_expected[0].id);
    EXPECT_EQ(user_response[1].nickname, user_response_expected[1].nickname);
    EXPECT_EQ(user_response[1].username, user_response_expected[1].username);
    EXPECT_EQ(user_response[1].id, user_response_expected[1].id);
}

TEST_F(TestUserUseCase, GetByIdSuccess) {
    UserResponseDTO user_response_expected(1,
                                           "user",
                                            "user");

    EXPECT_CALL(*user_rep, Find(1))
            .WillOnce(Return(*user));

    UserResponseDTO user_response = user_usecase->GetById(1);

    EXPECT_EQ(user_response.id, user_response_expected.id);
    EXPECT_EQ(user_response.nickname, user_response_expected.nickname);
    EXPECT_EQ(user_response.username, user_response_expected.username);
}

TEST_F(TestUserUseCase, GetByIdNotExist) {
    EXPECT_CALL(*user_rep, Find(1))
            .WillOnce(Return(nullopt));

    EXPECT_THROW(user_usecase->GetById(1), InvalidDataException);
}

TEST_F(TestUserUseCase, GetByIdNullPointer) {
    EXPECT_CALL(*user_rep, Find(1))
            .WillOnce(Return(*user_null));

    EXPECT_THROW(user_usecase->GetById(1), NullPointerException);
}
