#ifndef TESTS_INTTESTS_TEST_AUTH_USE_CASE_H_
#define TESTS_INTTESTS_TEST_AUTH_USE_CASE_H_

#include "gtest/gtest.h"

#include <memory>

#include "mus-irepo/iauth_repository.h"
#include "mus-usecase/auth_use_case.h"
#include "mus-dto/user_request_dto.h"

using std::shared_ptr;
using std::make_shared;
using music_share::IAuthRepository;
using music_share::AuthUseCase;

class TestAuthUseCase : public ::testing::Test {
protected:
    void SetUp() {
        shared_ptr<IAuthRepository> auth_rep = make_shared<AuthRepositoryPostgres>(connection_to_database);
        m_auth_use_case = make_shared<AuthUseCase>(*auth_rep);
        m_user_request = make_shared<UserRequestDTO>("Alex","Alex",
                                                     "alex", "alex@mail.ru");
    }
    void TearDown() { }
    shared_ptr<IAuthUseCase> m_auth_use_case;
    shared_ptr<UserRequestDTO> m_user_request;
};

TEST_F(TestAuthUseCase, Authorization) {
    EXPECT_TRUE(m_auth_use_case->Authorization(*m_user_request));
}

TEST_F(TestAuthUseCase, Authentication) {
    EXPECT_TRUE(m_auth_use_case->Authentication(*m_user_request));
}

#endif  // TESTS_INTTESTS_TEST_AUTH_USE_CASE_H_