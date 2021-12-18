#ifndef MUS_INTERNAL_MUS_DTO_USER_REQUEST_DTO_H_
#define MUS_INTERNAL_MUS_DTO_USER_REQUEST_DTO_H_

#include "reflectable/reflectable.h"

#include <tuple>
#include <cstdint>
#include <string>

struct UserRequestDTO {
    UserRequestDTO(const std::string& username_,
                   const std::string& password_,
                   const std::string& nickname_,
                   const std::string& email_)
                    : username(username_), password(password_),
                    nickname(nickname_), email(email_) {}

    std::string username;
    std::string password;
    std::string nickname;
    std::string email;

    constexpr static auto properties = std::tuple(
        music_share::reflectable::Property(&UserRequestDTO::username, "username"),
        music_share::reflectable::Property(&UserRequestDTO::password, "password"),
        music_share::reflectable::Property(&UserRequestDTO::nickname, "nickname"),
        music_share::reflectable::Property(&UserRequestDTO::email, "email")
    );
};

#endif  // MUS_INTERNAL_MUS_DTO_USER_REQUEST_DTO_H_
