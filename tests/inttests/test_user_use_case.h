#ifndef TESTS_INTTESTS_TEST_USER_USE_CASE_H_
#define TESTS_INTTESTS_TEST_USER_USE_CASE_H_

#include "gtest/gtest.h"

#include <memory>
#include <cstdint>
#include <vector>

#include "mus-iusecase/iuser_use_case.h"
#include "mus-irepo/iuser_repository.h"
#include "mus-usecase/user_use_case.h"
#include "mus-dto/user_request_dto.h"

using std::vector;
using std::string;
using std::shared_ptr;
using std::make_shared;
using music_share::IUserRepository;
using std::optional;
using std::nullopt;
using music_share::UserUseCase;

class TestUserUseCase : public ::testing::Test {
protected:
    void SetUp() {
        shared_ptr<IUserRepository> user_rep = make_shared<UserRepositoryPostgres>(connection_to_database);
        m_user_use_case = make_shared<UserUseCase>(*user_rep);
        m_user_request = make_shared<UserRequestDTO>("Alex", "Alex",
                                                     "alex", "alex@mail.ru");
        m_id = m_user_use_case->Create(*m_user_request);
    }
    void TearDown() { }

    shared_ptr<IUserUseCase> m_user_use_case;
    shared_ptr<UserRequestDTO> m_user_request;
    optional<uint32_t> m_id;
};

TEST_F(TestUserUseCase, Create) {
    UserRequestDTO user_request("Misha","Misha",
                                "misha", "misha@mail.ru");

    optional<uint32_t> id_ = m_user_use_case->Create(user_request);

    optional<UserResponseDTO> user_response = nullopt;
    if (id_) {
        user_response = m_user_use_case->GetById(*id_);
    }
    if (user_response) {
        EXPECT_EQ(user_response->nickname, user_request.nickname);
        EXPECT_EQ(user_response->username, user_request.username);
    }
}

TEST_F(TestUserUseCase, Update) {
    optional<UserResponseDTO> user_response = nullopt;
    string new_username("Misha");
    m_user_request->username = new_username;

    if (m_id) {
        user_response = m_user_use_case->Update(*m_id, *m_user_request);
    }

    if (user_response) {
        user_response = m_user_use_case->GetById(*m_id);
    }
    if (user_response) {
        EXPECT_EQ(user_response->id, *m_id);
        EXPECT_EQ(user_response->nickname, m_user_request.nickname);
        EXPECT_EQ(user_response->username, new_username);
    }
}

TEST_F(TestUserUseCase, GetByUsername) {
    vector<UserResponseDTO> user_response;
    string username("Alex");

    if (m_id) {
        user_response = m_user_use_case->GetByUsername(username);
    }

    EXPECT_EQ(user_response[0].id, m_id);
    EXPECT_EQ(user_response[0].nickname, m_user_request->nickname);
    EXPECT_EQ(user_response[0].username, username);
}

TEST_F(TestUserUseCase, GetByNickname) {
    optional<UserResponseDTO> user_response = nullopt;
    string nickname("alex");

    if (m_id) {
        user_response = m_user_use_case->GetByNickname(nickname);
    }


    if (user_response) {
        EXPECT_EQ(user_response->id, *m_id);
        EXPECT_EQ(user_response->nickname, m_user_request->nickname);
        EXPECT_EQ(user_response->username, m_user_request->username);
    }
}

TEST_F(TestUserUseCase, GetById) {
    optional<UserResponseDTO> user_response = nullopt;
    string nickname("alex");

    if (m_id) {
        user_response = m_user_use_case->GetById(*m_id);
    }

    if (user_response) {
        EXPECT_EQ(user_response->id, *m_id);
        EXPECT_EQ(user_response->nickname, m_user_request->nickname);
        EXPECT_EQ(user_response->username, m_user_request->username);
    }
}

#endif  // TESTS_INTTESTS_TEST_USER_USE_CASE_H_
