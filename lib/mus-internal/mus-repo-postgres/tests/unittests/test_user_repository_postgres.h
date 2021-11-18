#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

#include "mus-repo-postgres/user_repository_postgres.h"

using music_share::DbConnectionPostgres;
using music_share::UserRepositoryPostgres;
using music_share::User;

class TestUserRepositoryPostgres : public ::testing::Test {
protected:
    static constexpr std::string_view connection_string = "connection to test database";
    void SetUp() {
        m_db = std::make_unique<DbConnectionPostgres>(std::string(connection_string));
    }

    std::unique_ptr<DbConnectionPostgres> m_db;
};

TEST_F(TestUserRepositoryPostgres, Find) {
    // arrange
    User expected_user("nick", "nick@mail.ru",
                       "nickusr", "123123",
                       User::AccessLevel::Authorized, 1);

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(std::move(m_db));
    std::optional<User> actual_user = repo->Find(1);

    EXPECT_TRUE(actual_user.has_value());

    // assert
    EXPECT_STREQ(expected_user.GetUsername().c_str(), actual_user->GetUsername().c_str());
    EXPECT_STREQ(expected_user.GetNickname().c_str(), actual_user->GetNickname().c_str());
    EXPECT_STREQ(expected_user.GetEmail().c_str(), actual_user->GetEmail().c_str());
    EXPECT_STREQ(expected_user.GetPasswordHash().c_str(), actual_user->GetPasswordHash().c_str());
    EXPECT_EQ(expected_user.GetId(), actual_user->GetId());
}

TEST_F(TestUserRepositoryPostgres, Insert) {
    // arrange
    User expected_user("nick2", "2nick@mail.ru",
                       "2nickusr", "2123123",
                       User::AccessLevel::Authorized, 2);

    User user_to_create("nick2", "2nick@mail.ru",
                        "2nickusr", "2123123",
                        User::AccessLevel::Authorized, std::nullopt);

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(std::move(m_db));
    repo->Insert(user_to_create);

    // assert
    EXPECT_STREQ(expected_user.GetUsername().c_str(), user_to_create.GetUsername().c_str());
    EXPECT_STREQ(expected_user.GetNickname().c_str(), user_to_create.GetNickname().c_str());
    EXPECT_STREQ(expected_user.GetEmail().c_str(), user_to_create.GetEmail().c_str());
    EXPECT_STREQ(expected_user.GetPasswordHash().c_str(), user_to_create.GetPasswordHash().c_str());
    EXPECT_EQ(expected_user.GetId(), user_to_create.GetId());
}

TEST_F(TestUserRepositoryPostgres, Update) {
    // arrange
    User expected_user("nick2", "2nick@mail.ru",
                       "2nickusr", "2123123",
                       User::AccessLevel::Authorized, 3);

    User user_to_update("nick2", "2nick@mail.ru",
                        "2nickusr", "2123123",
                        User::AccessLevel::Authorized, 3);

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(std::move(m_db));
    repo->Update(user_to_update);

    // assert
    EXPECT_STREQ(expected_user.GetUsername().c_str(), user_to_update.GetUsername().c_str());
    EXPECT_STREQ(expected_user.GetNickname().c_str(), user_to_update.GetNickname().c_str());
    EXPECT_STREQ(expected_user.GetEmail().c_str(), user_to_update.GetEmail().c_str());
    EXPECT_STREQ(expected_user.GetPasswordHash().c_str(), user_to_update.GetPasswordHash().c_str());
    EXPECT_EQ(expected_user.GetId(), user_to_update.GetId());
}

TEST_F(TestUserRepositoryPostgres, Delete) {
    // arrange
    std::optional<User> expected_user = std::nullopt;

    User user_to_delete("nick2", "2nick@mail.ru",
                        "2nickusr", "2123123",
                        User::AccessLevel::Authorized, 3);

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(std::move(m_db));
    repo->Delete(user_to_delete);
    std::optional<User> actual_user = repo->Find(3);

    // assert
    EXPECT_FALSE(actual_user.has_value());
}

TEST_F(TestUserRepositoryPostgres, FindByNickname) {
    // arrange
    User expected_user("nick", "nick@mail.ru",
                       "nickusr", "123123",
                       User::AccessLevel::Authorized, 1);

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(std::move(m_db));
    std::vector<User> users = repo->FindByNickname("nick");


    // assert
    EXPECT_TRUE(users.size() == 1);
    const User& actual_user = users[0];

    EXPECT_STREQ(expected_user.GetUsername().c_str(), actual_user.GetUsername().c_str());
    EXPECT_STREQ(expected_user.GetNickname().c_str(), actual_user.GetNickname().c_str());
    EXPECT_STREQ(expected_user.GetEmail().c_str(), actual_user.GetEmail().c_str());
    EXPECT_STREQ(expected_user.GetPasswordHash().c_str(), actual_user.GetPasswordHash().c_str());
    EXPECT_EQ(expected_user.GetId(), actual_user.GetId());
}
