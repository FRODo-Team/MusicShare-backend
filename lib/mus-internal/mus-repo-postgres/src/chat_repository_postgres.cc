// Owners: Rostislav Vivcharuk, WEB-12
#include "mus-repo-postgres/chat_repository_postgres.h"

namespace music_share {

ChatRepositoryPostgres::ChatRepositoryPostgres(
        const std::string& connection_string)
        :
        m_crud_repository(connection_string, "mus_chat"),
        m_table_name(m_crud_repository.GetTableName()) { }

std::optional<Chat> ChatRepositoryPostgres::Find(uint32_t id) {
    return m_crud_repository.Find(id);
}

void ChatRepositoryPostgres::Insert(Chat& out_chat) {
    return m_crud_repository.Insert(out_chat);
}

void ChatRepositoryPostgres::Update(const Chat& chat) {
    return m_crud_repository.Update(chat);
}

void ChatRepositoryPostgres::Delete(const Chat& chat) {
    return m_crud_repository.Delete(chat);
}

std::vector<Chat> ChatRepositoryPostgres::FindByUserId(uint32_t user_id) {
    const std::string id = SqlUtils::ValueToSqlFormat(user_id);
    std::string query =
            "SELECT * FROM " + m_table_name + " " +
            "WHERE user_id_1=" + id + " OR user_id_2=" + id;

    pqxx::result response = m_crud_repository.ExecuteQuery(query);

    std::vector<Chat> result;
    for (const auto& row: response) {
        Chat c = SqlMapper::ToDomainObject(row);
        result.push_back(c);
    }

    return result;
}

std::optional<Chat> ChatRepositoryPostgres::FindByIdsOfUserPair(
        uint32_t first_user_id,
        uint32_t second_user_id)
{
    std::string query =
            "SELECT * FROM " + m_table_name + " " +
            "WHERE user_id_1=" + SqlUtils::ValueToSqlFormat(first_user_id) +
            "AND user_id_2=" + SqlUtils::ValueToSqlFormat(second_user_id);

    pqxx::result response = m_crud_repository.ExecuteQuery(query);
    if (response.empty()) {
        return { };
    }

    return SqlMapper::ToDomainObject(response[0]);
}


Chat ChatRepositoryPostgres::SqlMapper::ToDomainObject(const pqxx::row& row) {
    uint32_t user_id_1;
    uint32_t user_id_2;
    uint32_t id;

    for (const auto& field: row) {
        if (field.name() == std::string{ "user_id_1" }) {
            user_id_1 = field.as<uint32_t>();
        } else if (field.name() == std::string{ "user_id_2" }) {
            user_id_2 = field.as<uint32_t>();
        } else if (field.name() == std::string{ "id" }) {
            id = field.as<uint32_t>();
        }
    }

    return { {user_id_1, user_id_2}, id };
}

SqlObject ChatRepositoryPostgres::SqlMapper::ToSqlObject(const Chat& domain) {
    SqlObject o;

    o["user_id_1"] = SqlUtils::ValueToSqlFormat(domain.GetUserIds().first);
    o["user_id_2"] = SqlUtils::ValueToSqlFormat(domain.GetUserIds().second);
    if (domain.GetId().has_value()) {
        o["id"] = SqlUtils::ValueToSqlFormat(domain.GetId().value());
    }

    return o;
}

} // namespace music_share
