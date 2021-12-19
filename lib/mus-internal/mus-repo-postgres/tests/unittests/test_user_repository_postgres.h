#include <gtest/gtest.h>
#include <memory>
#include <fstream>
#include <sstream>
#include "mus-repo-postgres/user_repository_postgres.h"

using music_share::UserRepositoryPostgres;
using music_share::User;
using music_share::SqlUtils;
using music_share::DatabaseObject;

/* TODO (sunz):
 *      !   Добавить сравнения для User.playlist_ids     !
 */

class TestUserRepositoryPostgres : public ::testing::Test {
public:
    static void SetUpTestSuite() {
        DatabaseObject dbo(s_ConnectionString);
        for (const auto& filepath: s_TestDatabaseInitSqlScripts) {
            std::ifstream file(filepath);
            if (!file.is_open()) {
                throw std::runtime_error("Failed to read test database setup script");
            }
            std::stringstream buffer;
            buffer << file.rdbuf();
            std::string query = buffer.str();
            dbo.ExecuteQuery(query);
        }
    }

    static void TearDownTestSuite() {
        DatabaseObject dbo(s_ConnectionString);
        for (const auto& filepath: s_TestDatabaseDeinitSqlScripts) {
            std::ifstream file(filepath);
            if (!file.is_open()) {
                throw std::runtime_error("Failed to read test database teardown script");
            }
            std::stringstream buffer;
            buffer << file.rdbuf();
            std::string query = buffer.str();
            dbo.ExecuteQuery(query);
        }
    }

protected:
    static const std::string s_ConnectionString;
    static const std::vector<std::string> s_TestDatabaseInitSqlScripts;
    static const std::vector<std::string> s_TestDatabaseDeinitSqlScripts;
};

const std::string TestUserRepositoryPostgres::s_ConnectionString =
        DatabaseObject::MakeConnectionString("localhost", 5432, "sunz", "123123123", "mus_test_user");

// TODO: Написать конфиг файл для такого рода вещей
const std::vector<std::string> TestUserRepositoryPostgres::s_TestDatabaseInitSqlScripts = {
    std::string{ "/home/sunz/uni/parkmail-cpp/MusicShare-backend/db/postgres/migrations/v0001_021221_MUS-28_create_tables.sql" }
};

// TODO: Написать конфиг файл для такого рода вещей
const std::vector<std::string> TestUserRepositoryPostgres::s_TestDatabaseDeinitSqlScripts = {
    std::string{ "/home/sunz/uni/parkmail-cpp/MusicShare-backend/db/postgres/migrations/u0001_021221_MUS-28_create_tables.sql" }
};


TEST_F(TestUserRepositoryPostgres, FindNotExistingUser) {
    // arrange
    uint32_t user_id_to_find = 1028374;

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(s_ConnectionString);
    std::optional<User> actual_user = repo->Find(user_id_to_find);

    // assert
    ASSERT_FALSE(actual_user.has_value());
}

TEST_F(TestUserRepositoryPostgres, Insert)   {
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
            "INSERT INTO mus_user(username, email, password_hash, nickname, access_level) "
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

TEST_F(TestUserRepositoryPostgres, CheckIfUserHasPlaylists) {
    // arrange
    // TODO(sunz): move somewhere to fixture
    music_share::DatabaseObject db(s_ConnectionString);
    db.ExecuteQuery(
            "INSERT INTO mus_playlist(title, creator_id) "
            "VALUES"
            "('veryCoooolplaylistBraaaa', 1), "
            "('classic', 3)");

    db.ExecuteQuery(
            "INSERT INTO mus_song(title, artist, duration, url, year, album, genre) "
            "VALUES "
            "('Better Off Alone', 'Alice Deejay', '2.56', 'https://www.youtube.com/watch?v=Lgs9QUtWc3M', 1998, 'Unknown', 'trance'), "
            "('Better Off Alone', 'Alice Deejay', '2.56', '/somepath', 1998, 'Unknown', 'Unknown'), "
            "('Smooth Criminal', 'Alient Ant Farm', '3.33', '/music/nostalgic', 2001, 'Unknown', 'Punk')");

    db.ExecuteQuery(
            "INSERT INTO mus_playlist_has_song(playlist_id, song_id) "
            "VALUES"
            "(1, 1), "
            "(1, 2), "
            "(2, 1), "
            "(2, 2), "
            "(1, 3)");

    db.ExecuteQuery(
            "INSERT INTO mus_user_has_playlist(user_id, playlist_id)"
            "VALUES"
            "(1, 1), "
            "(1, 2), "
            "(3, 1)");

    const std::vector<uint32_t> expectedUserPlaylistIds = { 1, 2 };

    auto repo = std::make_unique<UserRepositoryPostgres>(s_ConnectionString);
    auto user = repo->Find(1);

    ASSERT_TRUE(user.has_value());
    ASSERT_EQ(expectedUserPlaylistIds.size(), user->playlist_ids.size());
    for (size_t i = 0; i < user->playlist_ids.size(); ++i) {
        ASSERT_EQ(expectedUserPlaylistIds[i], user->playlist_ids[i]);
    }
}

TEST_F(TestUserRepositoryPostgres, FetchAllNoLimit) {
    // Arrange
    const size_t expectedUserCount = 5;

    // act
    auto repo = std::make_unique<UserRepositoryPostgres>(s_ConnectionString);
    std::vector<User> actualUsers = repo->FetchAll();

    // Assert
    ASSERT_EQ(actualUsers.size(), expectedUserCount);
}
