#include <gtest/gtest.h>
#include <memory>

#include "mus-repo-postgres/user_repository_postgres.h"

using music_share::UserRepositoryPostgres;
using music_share::User;

/*
    Данный тест имеет смысл при наличии поднятой тестовой базы данных.
    TODO: Определить наполнение тестовой БД, Дописать FindByNickname.
 */

class TestUserRepositoryPostgres : public ::testing::Test {
protected:
    static const std::string s_ConnectionString;
};

const std::string TestUserRepositoryPostgres::s_ConnectionString = "connection to test database";


TEST_F(TestUserRepositoryPostgres, Find) {
    // arrange
    User expected_user("nick", "nick@mail.ru",
                       "nickusr", "123123",
                       User::AccessLevel::Authorized, 1);

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(s_ConnectionString);
    std::optional<User> actual_user = repo->Find(1);

    EXPECT_TRUE(actual_user.has_value());

    // assert
    if (actual_user) {
        EXPECT_STREQ(expected_user.GetUsername().c_str(), actual_user->GetUsername().c_str());
        EXPECT_STREQ(expected_user.GetNickname().c_str(), actual_user->GetNickname().c_str());
        EXPECT_STREQ(expected_user.GetEmail().c_str(), actual_user->GetEmail().c_str());
        EXPECT_STREQ(expected_user.GetPasswordHash().c_str(), actual_user->GetPasswordHash().c_str());
        EXPECT_EQ(expected_user.GetId(), actual_user->GetId());
    }
}

TEST_F(TestUserRepositoryPostgres, FindNotExistingUser) {
    // arrange
    uint32_t user_id_to_find = 1028374;

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(s_ConnectionString);
    std::optional<User> actual_user = repo->Find(user_id_to_find);

    // assert
    EXPECT_FALSE(actual_user.has_value());
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
    auto repo = std::make_unique<UserRepositoryPostgres>(s_ConnectionString);
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
    const uint32_t id = 3;

    User user_to_update("UPDATED_NICKNAME", "2nick@mail.ru",
                        "2nickusr", "2123123",
                        User::AccessLevel::Authorized, id);

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(s_ConnectionString);
    repo->Update(user_to_update);

    // assert
    std::optional<User> user_updated = repo->Find(id);
    EXPECT_TRUE(user_updated.has_value());
    if (user_updated) {
        EXPECT_STREQ(user_updated->GetUsername().c_str(), user_to_update.GetUsername().c_str());
        EXPECT_STREQ(user_updated->GetNickname().c_str(), user_to_update.GetNickname().c_str());
        EXPECT_STREQ(user_updated->GetEmail().c_str(), user_to_update.GetEmail().c_str());
        EXPECT_STREQ(user_updated->GetPasswordHash().c_str(), user_to_update.GetPasswordHash().c_str());
        EXPECT_EQ(user_updated->GetId(), user_to_update.GetId());
    }
}

TEST_F(TestUserRepositoryPostgres, Delete) {
    // arrange
    std::optional<User> expected_user = std::nullopt;

    User user_to_delete("nick2", "2nick@mail.ru",
                        "2nickusr", "2123123",
                        User::AccessLevel::Authorized, 3);

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(s_ConnectionString);
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
    auto repo = std::make_unique<UserRepositoryPostgres>(s_ConnectionString);
    std::vector<User> users = repo->FindByNickname("nick");


    // assert
    EXPECT_TRUE(users.size() > 0);
    const User& actual_user = users[0];

    EXPECT_STREQ(expected_user.GetUsername().c_str(), actual_user.GetUsername().c_str());
    EXPECT_STREQ(expected_user.GetNickname().c_str(), actual_user.GetNickname().c_str());
    EXPECT_STREQ(expected_user.GetEmail().c_str(), actual_user.GetEmail().c_str());
    EXPECT_STREQ(expected_user.GetPasswordHash().c_str(), actual_user.GetPasswordHash().c_str());
    EXPECT_EQ(expected_user.GetId(), actual_user.GetId());
}
