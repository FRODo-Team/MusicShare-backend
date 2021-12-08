#include "mus-usecase/user_use_case.h"

#include <memory>
#include <optional>

#include "mus-usecase/exception/create_exception.h"
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
        auto user = make_unique<User>(user_dto.nickname,
                                                    user_dto.email,
                                                    user_dto.username,
                                                    user_dto.password,
                                                    User::AccessLevel::Authorized);

        m_user_rep.Insert(*user);

        if (!user->GetId()) {
            throw CreateException();
        }
        return *user->GetId();
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

    UserResponseDTO UserUseCase::GetByUsername(const string& username) {
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

    vector<UserResponseDTO> UserUseCase::GetByNickname(const string& nickname) {
        vector<User> users = m_user_rep.FindByNickname(nickname);

         if (users.empty()) {
             throw InvalidDataException();
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

    UserResponseDTO UserUseCase::GetByEmail(const string& email) {
        optional<User> user = m_user_rep.FindByEmail(email);

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

    UserResponseDTO UserUseCase::GetById(uint32_t id) {
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

    void UserUseCase::DeleteById(uint32_t id) {
        optional<User> user = m_user_rep.Find(id);

        if (!user) {
            throw InvalidDataException();
        }
        if (!user->GetId()) {
            throw NullPointerException();
        }

        m_user_rep.Delete(*user);
    }

}  // namespace music_share
