#include <gtest/gtest.h>
#include <memory>

#include "mus-repo-postgres/user_repository_postgres.h"

using music_share::UserRepositoryPostgres;
using music_share::User;
using music_share::SqlUtils;

/*
    Данный тест имеет смысл при наличии поднятой тестовой базы данных.
    TODO: Определить наполнение тестовой БД, Дописать FindByNickname.
 */

class TestUserRepositoryPostgres : public ::testing::Test {
protected:
    static const std::string s_ConnectionString;
};

const std::string TestUserRepositoryPostgres::s_ConnectionString =
        SqlUtils::MakeConnectionString(
                "localhost", 5432, "sunz", "123123123", "mus_test");


TEST_F(TestUserRepositoryPostgres, FindNotExistingUser) {
    // arrange
    uint32_t user_id_to_find = 1028374;

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(s_ConnectionString);
    std::optional<User> actual_user = repo->Find(user_id_to_find);

    // assert
    ASSERT_FALSE(actual_user.has_value());
}

TEST_F(TestUserRepositoryPostgres, Insert) {
    // arrange
    User expected_user("username1", "mail1@mail.ru",
                       "123", "nickname1",
                       User::AccessLevel::Authorized, 1);

    User user_to_create("username1", "mail1@mail.ru",
                        "123", "nickname1",
                        User::AccessLevel::Authorized, { });

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(s_ConnectionString);
    repo->Insert(user_to_create);

    // assert
    ASSERT_STREQ(expected_user.GetUsername().c_str(),
                 user_to_create.GetUsername().c_str());

    ASSERT_STREQ(expected_user.GetNickname().c_str(),
                 user_to_create.GetNickname().c_str());

    ASSERT_STREQ(expected_user.GetEmail().c_str(),
                 user_to_create.GetEmail().c_str());

    ASSERT_STREQ(expected_user.GetPasswordHash().c_str(),
                 user_to_create.GetPasswordHash().c_str());

    ASSERT_EQ(expected_user.GetId(), user_to_create.GetId());
}

TEST_F(TestUserRepositoryPostgres, Find) {
    // arrange
    User expected_user("username1", "mail1@mail.ru",
                       "123", "nickname1",
                       User::AccessLevel::Authorized, 1);

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(s_ConnectionString);
    std::optional<User> actual_user = repo->Find(1);

    ASSERT_TRUE(actual_user.has_value());

    // assert
    if (actual_user) {
        ASSERT_STREQ(expected_user.GetUsername().c_str(),
                     actual_user->GetUsername().c_str());

        ASSERT_STREQ(expected_user.GetNickname().c_str(),
                     actual_user->GetNickname().c_str());

        ASSERT_STREQ(expected_user.GetEmail().c_str(),
                     actual_user->GetEmail().c_str());

        ASSERT_STREQ(expected_user.GetPasswordHash().c_str(),
                     actual_user->GetPasswordHash().c_str());

        ASSERT_EQ(expected_user.GetId(), actual_user->GetId());
    }
}

TEST_F(TestUserRepositoryPostgres, Update) {
    // arrange
    const uint32_t id = 1;

    User user_to_update("UPDATED", "mail1@mail.ru",
                       "123", "nickname1",
                       User::AccessLevel::Authorized, 1);

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(s_ConnectionString);
    repo->Update(user_to_update);

    // assert
    std::optional<User> user_updated = repo->Find(id);
    ASSERT_TRUE(user_updated.has_value());
    if (user_updated) {
        ASSERT_STREQ(user_updated->GetUsername().c_str(),
                     user_to_update.GetUsername().c_str());

        ASSERT_STREQ(user_updated->GetNickname().c_str(),
                     user_to_update.GetNickname().c_str());

        ASSERT_STREQ(user_updated->GetEmail().c_str(),
                     user_to_update.GetEmail().c_str());

        ASSERT_STREQ(user_updated->GetPasswordHash().c_str(),
                     user_to_update.GetPasswordHash().c_str());

        ASSERT_EQ(user_updated->GetId(), user_to_update.GetId());
    }
}

TEST_F(TestUserRepositoryPostgres, Delete) {
    // TODO(sunz): move somewhere to fixture
    music_share::DatabaseObject db(s_ConnectionString);
    db.ExecuteQuery(
            "INSERT INTO mus_user(username, email, password_hash, nickname, access_level)"
            "VALUES ('username2', 'mail2@mail.ru', '321', 'nickname2', 1)");

    // arrange
    std::optional<User> expected_user = { };
    const uint32_t id = 2;

    User user_to_delete("username2", "mail2@mail.ru", "321", "nickname2",
                        User::AccessLevel::Authorized,
                        id);

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(s_ConnectionString);
    repo->Delete(user_to_delete);
    std::optional<User> actual_user = repo->Find(id);

    // assert
    ASSERT_FALSE(actual_user.has_value());
}


TEST_F(TestUserRepositoryPostgres, FindByNickname) {
    // TODO(sunz): move somewhere to fixture
    music_share::DatabaseObject db(s_ConnectionString);
    db.ExecuteQuery(
            "INSERT INTO mus_user(username, email, password_hash, nickname, access_level)"
            "VALUES"
                "('username3', 'mail3@mail.ru', '321', 'PopularNickname', 1), "
                "('username4', 'mail4@mail.ru', '321', 'PopularNickname', 1), "
                "('username5', 'mail5@mail.ru', '321', 'PopularNickname', 1), "
                "('username6', 'mail6@mail.ru', '321', 'PopularNickname', 1)");

    // arrange
    const std::string popularNickname = "PopularNickname";
    std::vector<User> expectedUsers = {
            User("username3", "mail3@mail.ru", "321", popularNickname, User::AccessLevel::Authorized, 3),
            User("username4", "mail4@mail.ru", "321", popularNickname, User::AccessLevel::Authorized, 4),
            User("username5", "mail5@mail.ru", "321", popularNickname, User::AccessLevel::Authorized, 5),
            User("username6", "mail6@mail.ru", "321", popularNickname, User::AccessLevel::Authorized, 6),
    };

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(s_ConnectionString);
    std::vector<User> actualUsers = repo->FindByNickname(popularNickname);

    // assert
    ASSERT_TRUE(actualUsers.size() == 4);

    for (size_t i = 0; i < actualUsers.size(); i++) {
        const auto& expected_user = expectedUsers[i];
        const auto& actual_user = actualUsers[i];

        ASSERT_STREQ(expected_user.GetUsername().c_str(),
                     actual_user.GetUsername().c_str());

        ASSERT_STREQ(expected_user.GetNickname().c_str(),
                     actual_user.GetNickname().c_str());

        ASSERT_STREQ(expected_user.GetEmail().c_str(),
                     actual_user.GetEmail().c_str());

        ASSERT_STREQ(expected_user.GetPasswordHash().c_str(),
                     actual_user.GetPasswordHash().c_str());

        ASSERT_EQ(expected_user.GetId(), actual_user.GetId());
    }
}

TEST_F(TestUserRepositoryPostgres, FindByUsername) {
    // arrange
    User expected_user("username3", "mail3@mail.ru", "321", "PopularNickname",
                       User::AccessLevel::Authorized, 3);
    const std::string username = "username3";

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(s_ConnectionString);
    std::optional<User> actual_user = repo->FindByUsername(username);

    // assert
    ASSERT_TRUE(actual_user.has_value());
    if (actual_user.has_value()) {
        ASSERT_STREQ(expected_user.GetUsername().c_str(),
                     actual_user->GetUsername().c_str());

        ASSERT_STREQ(expected_user.GetNickname().c_str(),
                     actual_user->GetNickname().c_str());

        ASSERT_STREQ(expected_user.GetEmail().c_str(),
                     actual_user->GetEmail().c_str());

        ASSERT_STREQ(expected_user.GetPasswordHash().c_str(),
                     actual_user->GetPasswordHash().c_str());

        ASSERT_EQ(expected_user.GetId(), actual_user->GetId());
    }
}

TEST_F(TestUserRepositoryPostgres, FindByUsernameNotExisting) {
    // arrange
    const std::string username = "username1488";

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(s_ConnectionString);
    std::optional<User> actual_user = repo->FindByUsername(username);

    // assert
    ASSERT_FALSE(actual_user.has_value());
}

TEST_F(TestUserRepositoryPostgres, FindByEmail) {
    // arrange
    const std::string email = "mail3@mail.ru";
    User expected_user("username3", email, "321", "PopularNickname",
                      User::AccessLevel::Authorized, 3);

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(s_ConnectionString);
    std::optional<User> actual_user = repo->FindByEmail(email);

    // assert
    ASSERT_TRUE(actual_user.has_value());
    if (actual_user.has_value()) {
        ASSERT_STREQ(expected_user.GetUsername().c_str(),
                     actual_user->GetUsername().c_str());

        ASSERT_STREQ(expected_user.GetNickname().c_str(),
                     actual_user->GetNickname().c_str());

        ASSERT_STREQ(expected_user.GetEmail().c_str(),
                     actual_user->GetEmail().c_str());

        ASSERT_STREQ(expected_user.GetPasswordHash().c_str(),
                     actual_user->GetPasswordHash().c_str());

        ASSERT_EQ(expected_user.GetId(), actual_user->GetId());
    }
}

TEST_F(TestUserRepositoryPostgres, FindByEmailNotExisting) {
    // arrange
    const std::string email = "nagibator2005@mail.ru";

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(s_ConnectionString);
    std::optional<User> actualUser = repo->FindByEmail(email);

    // assert
    ASSERT_FALSE(actualUser.has_value());
}
