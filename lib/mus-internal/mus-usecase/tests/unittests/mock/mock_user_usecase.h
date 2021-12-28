#ifndef MUS_INTERNAL_MOCK_MOCK_USER_USECASE_H
#define MUS_INTERNAL_MOCK_MOCK_USER_USECASE_H

#include <gmock/gmock.h>
#include <optional>
#include <cstdint>
#include <string>
#include <vector>

#include "mus-iusecase/iuser_use_case.h"
#include "mus-dto/user_response_dto.h"

using std::string;
using std::optional;
using std::vector;

using music_share::IUserUseCase;

class MockUserUseCase : public IUserUseCase {
public:
    MOCK_METHOD1(Create, uint32_t(const UserRequestDTO&));
    MOCK_METHOD2(Update, UserResponseDTO(uint32_t, const UserRequestDTO&));
    MOCK_CONST_METHOD1(GetByUsername, UserResponseDTO(const string&));
    MOCK_CONST_METHOD1(GetByNicknames,
                       vector<UserResponseDTO>(const std::vector<std::string>));
    MOCK_CONST_METHOD1(GetById, UserResponseDTO(uint32_t));
};

#endif  // MUS_INTERNAL_MOCK_MOCK_USER_USECASE_H
