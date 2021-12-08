#ifndef MUS_INTERNAL_MUS_DTO_USER_RESPONSE_DTO_H_
#define MUS_INTERNAL_MUS_DTO_USER_RESPONSE_DTO_H_

#include <cstdint>
#include <string>

struct UserResponseDTO {
    UserResponseDTO(uint32_t id_,
                    const std::string& username_,
                    const std::string& nickname_)
                    : id(id_), username(username_),
                    nickname(nickname_) {}

    uint32_t id;
    std::string username;
    std::string nickname;
};

#endif  // MUS_INTERNAL_MUS_DTO_USER_RESPONSE_DTO_H_
