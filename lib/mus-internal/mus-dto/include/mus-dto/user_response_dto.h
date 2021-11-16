#ifndef MUS_INTERNAL_MUS_DTO_USER_RESPONSE_DTO_H_
#define MUS_INTERNAL_MUS_DTO_USER_RESPONSE_DTO_H_

#include <string>

struct UserResponseDTO {
    UserResponseDTO(int id_, std::string username_,
                    std::string nickname_)
                    : id(id_), username(username_), nickname(nickname_) {}

    int id;
    std::string username;
    std::string nickname;
};

#endif  // MUS_INTERNAL_MUS_DTO_USER_RESPONSE_DTO_H_
