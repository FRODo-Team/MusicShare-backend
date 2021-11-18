#ifndef MUS_MUSINTERNAL_MUSCONTROLLER_USERCONTROLLER_H_
#define MUS_MUSINTERNAL_MUSCONTROLLER_USERCONTROLLER_H_

#include "mus-controller/endpoint.h"

#include <memory>  // std::shared_ptr

#include "mus-dto/user_request_dto.h"  // music_share::UserRequestDTO
#include "mus-dto/user_response_dto.h"  // music_share::UserRequestDTO
#include "mus-usecase/user_use_case.h"  // music_share::UserUseCase
#include "mus-controller/request.h"
#include "mus-controller/response.h"

namespace music_share {

class UserController {
public:
    using Request = Request<UserRequestDTO>;
    using Response = Response<UserResponseDTO>;

    UserController();
    ~UserController() = default;

    Response User(const Request& response) {
        return m_user_endpoint(response);
    }
    Response UserID(const Request& response) {
        return m_user_id_endpoint(response);
    }
private:
    class UserEndpoint : public Endpoint<Request, Response> {
    public:
        UserEndpoint(std::shared_ptr<IUserUseCase> user_usecase);

        virtual Response Get(const Request& request) {
            return Response();
        }
        virtual Response Post(const Request& request) {
            return Response();
        }
    private:
        std::shared_ptr<IUserUseCase> m_user_usecase;
    };

    class UserIDEndpoint : public Endpoint<Request, Response> {
    public:
        UserIDEndpoint(std::shared_ptr<IUserUseCase> user_usecase);

        virtual Response Get(const Request& request) {
            return Response();
        }
        virtual Response Patch(const Request& request) {
            return Response();
        }
    private:
        std::shared_ptr<IUserUseCase> m_user_usecase;
    };

    std::shared_ptr<IUserUseCase> m_user_usecase;
    UserEndpoint m_user_endpoint;
    UserIDEndpoint m_user_id_endpoint;
};

}  // namespace music_share

#endif  // MUS_MUSINTERNAL_MUSCONTROLLER_USERCONTROLLER_H_
