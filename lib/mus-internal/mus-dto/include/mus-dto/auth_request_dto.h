#ifndef MUS_INTERNAL_MUS_DTO_AUTHREQUESTDTO_H_
#define MUS_INTERNAL_MUS_DTO_AUTHREQUESTDTO_H_

#include "reflectable/reflectable.h"

#include <tuple>
#include <cstdint>
#include <string>

struct AuthRequestDTO {
    AuthRequestDTO(const std::string& username_, const std::string& password_)
        : username(username_), password(password_) { }

    std::string username;
    std::string password;

    constexpr static auto properties = std::tuple(
        music_share::reflectable::Property(&AuthRequestDTO::username, "username"),
        music_share::reflectable::Property(&AuthRequestDTO::password, "password")
    );
};

#endif // MUS_INTERNAL_MUS_DTO_AUTHREQUESTDTO_H_
