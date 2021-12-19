#include <cassert>
#include "mus-repo-postgres/user_repository_postgres.h"


namespace music_share {

UserRepositoryPostgres::UserRepositoryPostgres(
        const std::string& connection_string)
        :
        m_crud_repository(connection_string, "mus_user"),
        m_table_name(m_crud_repository.GetTableName()) { }


std::optional<User> UserRepositoryPostgres::Find(uint32_t id) {
    std::optional<User> user = m_crud_repository.Find(id);
    if (!user.has_value()) {
        return { };
    }

    std::string query =
            "SELECT playlist_id FROM " + std::string(kUserHasPlaylistTableName) +
            " WHERE user_id=" + SqlUtils::ValueToSqlFormat(id);

    pqxx::result response = m_crud_repository.ExecuteQuery(query);

    std::vector<uint32_t> fetched_playlist_ids;
    for (const auto& row: response) {
        auto playlist_id = row[0].as<uint32_t>();
        fetched_playlist_ids.push_back(playlist_id);
    }

    user->playlist_ids = fetched_playlist_ids;
    return user;
}

void UserRepositoryPostgres::Insert(User& out_obj) {
    m_crud_repository.Insert(out_obj);

    const uint32_t user_id = out_obj.GetId().value();

    // TODO: rewrite in single query.
    for (uint32_t playlist_id: out_obj.playlist_ids) {
        std::string query =
                "INSERT INTO " +  std::string(kUserHasPlaylistTableName) + " " +
                "(user_id, playlist_id) VALUES(" +
                SqlUtils::ValueToSqlFormat(user_id) + ", " +
                SqlUtils::ValueToSqlFormat(playlist_id) + ")" +
                "ON CONFLICT DO NOTHING";
        m_crud_repository.ExecuteQuery(query);
    }
}

void UserRepositoryPostgres::Update(const User& obj) {
    m_crud_repository.Update(obj);

    const uint32_t user_id = obj.GetId().value();

    // TODO: rewrite in single query.
    for (uint32_t playlist_id: obj.playlist_ids) {
        std::string query =
                "INSERT INTO " +  std::string(kUserHasPlaylistTableName) + " " +
                "(user_id, playlist_id) VALUES(" +
                SqlUtils::ValueToSqlFormat(user_id) + ", " +
                SqlUtils::ValueToSqlFormat(playlist_id) + ")" +
                "ON CONFLICT DO NOTHING";
        m_crud_repository.ExecuteQuery(query);
    }
}

void UserRepositoryPostgres::Delete(const User& obj) {
    return m_crud_repository.Delete(obj);
}

std::vector<User> UserRepositoryPostgres::FetchAll(
        std::optional<uint32_t> limit)
{
    std::string query = "SELECT id FROM " + m_table_name;
    if (limit.has_value()) {
        query += " LIMIT " + SqlUtils::ValueToSqlFormat(limit.value());
    }

    std::vector<User> result;

    pqxx::result response = m_crud_repository.ExecuteQuery(query);
    for (const auto& row: response) {
        assert(row[0].name() == std::string{ "id" });
        const auto id = row[0].as<uint32_t>();
        std::optional<User> u = Find(id);
        result.push_back(*u);
    }

    return result;
}

std::optional<User> UserRepositoryPostgres::FindByUsername(
        const std::string& username)
{
    std::string query =
            "SELECT id FROM " + m_table_name + " " +
            "WHERE username=" + SqlUtils::ValueToSqlFormat(username);

    pqxx::result response = m_crud_repository.ExecuteQuery(query);
    if (response.empty()) {
        return { };
    }

    assert(response[0][0].name() == std::string{ "id" });
    const auto id = response[0][0].as<uint32_t>();

    return Find(id);
}

std::optional<User> UserRepositoryPostgres::FindByEmail(
        const std::string& email)
{
    std::string query =
            "SELECT id FROM " + m_table_name + " " +
            "WHERE email=" + SqlUtils::ValueToSqlFormat(email);

    pqxx::result response = m_crud_repository.ExecuteQuery(query);
    if (response.empty()) {
        return { };
    }

    assert(response[0][0].name() == std::string{ "id" });
    const auto id = response[0][0].as<uint32_t>();

    return Find(id);
}

std::vector<User> UserRepositoryPostgres::FindByNickname(
        const std::string& nickname)
{
    std::string query =
            "SELECT id FROM " + m_table_name + " " +
            "WHERE nickname=" + SqlUtils::ValueToSqlFormat(nickname);

    pqxx::result response = m_crud_repository.ExecuteQuery(query);

    std::vector<User> result;
    for (const auto& row: response) {
        assert(row[0].name() == std::string{ "id" });
        const auto id = row[0].as<uint32_t>();
        std::optional<User> u = Find(id);
        result.push_back(*u);
    }

    return result;
}

User UserRepositoryPostgres::SqlMapperForUserTable::ToDomainObject(
        const pqxx::row& row)
{
    std::string username;
    std::string email;
    std::string password_hash;
    std::string nickname;
    User::AccessLevel access_level;
    uint32_t id;

    for (const auto& field: row) {
        if (field.name() == std::string{ "id" }) {
            id = field.as<uint32_t>();
        } else if (field.name() == std::string{ "nickname" }) {
            nickname = field.as<std::string>();
        } else if (field.name() == std::string{ "email" }) {
            email = field.as<std::string>();
        } else if (field.name() == std::string{ "username" }) {
            username = field.as<std::string>();
        } else if (field.name() == std::string{ "password_hash" }) {
            password_hash = field.as<std::string>();
        } else if (field.name() == std::string{ "access_level" }) {
            access_level = static_cast<User::AccessLevel>(field.as<int>());
        }
    }

    return { username, email, password_hash, nickname, access_level, id };
}

SqlObject UserRepositoryPostgres::SqlMapperForUserTable::ToSqlObject(
        const User& domain)
{
    SqlObject result;

    result["nickname"] = SqlUtils::ValueToSqlFormat(domain.GetNickname());
    result["email"] = SqlUtils::ValueToSqlFormat(domain.GetEmail());
    result["username"] = SqlUtils::ValueToSqlFormat(domain.GetUsername());
    result["password_hash"] =
            SqlUtils::ValueToSqlFormat(domain.GetPasswordHash());
    result["access_level"] =
            SqlUtils::ValueToSqlFormat(static_cast<int>(domain.GetAccessLevel()));
    if (domain.GetId().has_value()) {
        result["id"] = SqlUtils::ValueToSqlFormat(domain.GetId().value());
    }

    return result;
}

} // namespace music_share
