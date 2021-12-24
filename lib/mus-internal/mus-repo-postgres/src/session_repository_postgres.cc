#include "mus-repo-postgres/session_repository_postgres.h"

namespace music_share {

SessionRepositoryPostgres::SessionRepositoryPostgres(
        const std::string& connection_string)
        :
        m_crud_repository(connection_string, std::string(kTableName)),
        m_table_name(kTableName) { }

std::optional<Session> SessionRepositoryPostgres::Find(uint32_t id) {
    return m_crud_repository.Find(id);
}

void SessionRepositoryPostgres::Insert(Session& out_obj) {
    return m_crud_repository.Insert(out_obj);
}

void SessionRepositoryPostgres::Update(const Session& obj) {
    return m_crud_repository.Update(obj);
}

void SessionRepositoryPostgres::Delete(const Session& obj) {
    return m_crud_repository.Delete(obj);
}

std::optional<Session> SessionRepositoryPostgres::FindBySessionKey(
        const std::string& key)
{
    std::string key_sql = SqlUtils::ValueToSqlFormat(key);
    std::string query =
            "SELECT * FROM " + std::string(kTableName) +
            "WHERE session_key=" + key_sql;

    pqxx::result response = m_crud_repository.ExecuteQuery(query);
    if (response.empty()) {
        return { };
    }

    Session s = SqlMapper::ToDomainObject(response[0]);
    return s;
}

Session SessionRepositoryPostgres::SqlMapper::ToDomainObject(
        const pqxx::row& row)
{
    std::optional<uint32_t> id;
    uint32_t user_id;
    std::string date_expires;
    std::string session_key;

    for (const auto &field: row) {
        if (field.name() == std::string{"id"}) {
            id = field.as<uint32_t>();
        } else if (field.name() == std::string{ "user_id" }) {
            user_id = field.as<uint32_t>();
        } else if (field.name() == std::string{ "datetime_expires" }) {
            date_expires = field.as<std::string>();
        } else if (field.name() == std::string{ "session_key" }) {
            session_key = field.as<std::string>();
        }
    }

    return { user_id, session_key, date_expires, id };
}

SqlObject SessionRepositoryPostgres::SqlMapper::ToSqlObject(
        const Session& domain)
{
    SqlObject result;

    if (domain.GetId().has_value()) {
        result["id"] = domain.GetId().value();
    }
    result["user_id"] = domain.GetUserId();
    result["session_key"] = domain.GetSessionKey();
    result["date_expires"] = domain.GetDateExpires();

    return result;
}

} // namespace music_share
