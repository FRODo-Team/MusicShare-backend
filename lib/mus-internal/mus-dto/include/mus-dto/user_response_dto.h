#ifndef MUS_INTERNAL_MUS_DTO_USER_RESPONSE_DTO_H_
#define MUS_INTERNAL_MUS_DTO_USER_RESPONSE_DTO_H_

#include "reflectable/reflectable.h"

#include <tuple>
#include <string>
#include <cstdint>

struct UserResponseDTO {
    UserResponseDTO(uint32_t id_,
                    const std::string& username_,
                    const std::string& nickname_)
                    : id(id_), username(username_),
                    nickname(nickname_) {}

    uint32_t id;
    std::string username;
    std::string nickname;

    constexpr static auto properties = std::tuple(
        music_share::reflectable::Property(&UserResponseDTO::id, "id"),
        music_share::reflectable::Property(&UserResponseDTO::username, "username"),
        music_share::reflectable::Property(&UserResponseDTO::nickname, "nickname")
    );
};

#endif  // MUS_INTERNAL_MUS_DTO_USER_RESPONSE_DTO_H_
