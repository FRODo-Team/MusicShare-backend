#ifndef MUS_INTERNAL_MUS_DTO_USER_REQUEST_DTO_H_
#define MUS_INTERNAL_MUS_DTO_USER_REQUEST_DTO_H_

#include <cstdint>
#include <string>

struct UserRequestDTO {
    UserRequestDTO(std::string username_, std::string password_,
                   std::string nickname_, std::string email_)
                    : username(username_), password(password_),
                    nickname(nickname_), id(id_), email(email_) {}

    std::string username;
    std::string password;
    std::string nickname;
    std::string email;
};

#endif  // MUS_INTERNAL_MUS_DTO_USER_REQUEST_DTO_H_
