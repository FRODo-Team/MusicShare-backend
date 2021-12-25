// Oweners: Darya Vlaskina, ML-13
#include "mus-usecase/user_use_case.h"
#include "mus-utility/crypto.h"

#include <memory>
#include <optional>

#include "mus-usecase/exception/create_exception.h"
#include "mus-usecase/exception/exist_exception.h"
#include "mus-usecase/exception/invalid_data_exception.h"
#include "mus-usecase/exception/null_pointer_exception.h"

using std::make_unique;
using std::nullopt;
using std::optional;
using std::string;
using std::vector;

namespace music_share {

    UserUseCase::UserUseCase(IUserRepository& user_rep)
                            : m_user_rep(user_rep) { }

    UserUseCase::UserUseCase(const UserUseCase& user_use_case)
                            : m_user_rep(user_use_case.m_user_rep) { }

    UserUseCase& UserUseCase::operator=(const UserUseCase& user_use_case) {
        m_user_rep = user_use_case.m_user_rep;
        return *this;
    }

    uint32_t UserUseCase::Create(const UserRequestDTO& user_dto) {
        optional<User> user_exist = m_user_rep.FindByUsername(user_dto.username);
        if (user_exist) {
            throw ExistException();
        }

        user_exist = m_user_rep.FindByEmail(user_dto.email);
        if (user_exist) {
            throw ExistException();
        }

        std::string hashed_password =
                utility::Crypto::HashString_SHA256(user_dto.password);

        User user(user_dto.username,
                  user_dto.email,
                  hashed_password,
                  user_dto.nickname,
                  User::AccessLevel::Authorized);

        m_user_rep.Insert(user);

        if (!user.GetId()) {
            throw CreateException();
        }
        return *user.GetId();
    }

    UserResponseDTO UserUseCase::Update(uint32_t user_id,
                                        const UserRequestDTO& user_dto) {
        User user(user_dto.username,
                  user_dto.email,
                  user_dto.password,
                  user_dto.nickname,
                  User::AccessLevel::Authorized,
                  user_id);

        m_user_rep.Update(user);

        return UserResponseDTO(user_id,
                               user_dto.username,
                               user_dto.nickname);
    }

    UserResponseDTO UserUseCase::GetByUsername(const string& username) const {
        optional<User> user = m_user_rep.FindByUsername(username);

        if (!user) {
            throw InvalidDataException();
        }
        if (!user->GetId()) {
            throw NullPointerException();
        }

        return UserResponseDTO(*user->GetId(),
                               user->GetUsername(),
                               user->GetNickname());
    }

    vector<UserResponseDTO> UserUseCase::GetByNicknames(const vector<string> nicknames) const {
        vector<User> users;

        if (nicknames.empty()) {
            users = m_user_rep.FetchAll();
        } else {
            users.reserve(nicknames.size());
            for (const string& nickname : nicknames) {
                vector<User> found_users = m_user_rep.FindByNickname(nickname);
                users.insert(users.end(),
                             found_users.begin(),
                             found_users.end());
            }
        }

        if (users.empty()) {
            return {};
        }

         vector<UserResponseDTO> users_dto;
         users_dto.reserve(users.size());
         for (const User& user : users) {
             if (!user.GetId()) {
                 throw NullPointerException();
             }
             users_dto.emplace_back(*user.GetId(),
                                   user.GetUsername(),
                                   user.GetNickname());
         }

         return users_dto;
    }

    UserResponseDTO UserUseCase::GetById(uint32_t id) const {
        optional<User> user = m_user_rep.Find(id);

        if (!user) {
            throw InvalidDataException();
        }
        if (!user->GetId()) {
            throw NullPointerException();
        }

        return UserResponseDTO(*user->GetId(),
                               user->GetUsername(),
                               user->GetNickname());
    }

}  // namespace music_share
