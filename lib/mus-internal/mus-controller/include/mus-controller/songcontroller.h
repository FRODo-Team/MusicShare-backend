#ifndef MUS_MUSINTERNAL_MUSCONTROLLER_SongCONTROLLER_H_
#define MUS_MUSINTERNAL_MUSCONTROLLER_SongCONTROLLER_H_

#include "mus-controller/endpoint.h"

#include <memory>  // std::shared_ptr

#include "mus-dto/song_response_dto.h"  // music_share::SongRequestDTO
#include "mus-usecase/song_use_case.h"  // music_share::SongUseCase
#include "mus-controller/request.h"
#include "mus-controller/response.h"

namespace music_share {

class SongController {
public:
    struct EmptyBody;
    using Request = Request<EmptyBody>;
    using Response = Response<SongResponseDTO>;

    SongController();
    ~SongController() = default;

    Response Song(const Request& response) {
        return m_song_endpoint(response);
    }
    Response SongID(const Request& response) {
        return m_song_id_endpoint(response);
    }
private:
    class SongEndpoint : public Endpoint<Request, Response> {
    public:
        SongEndpoint(std::shared_ptr<ISongUseCase> song_usecase);

        virtual Response Get(const Request& request) {
            return Response();
        }
    private:
        std::shared_ptr<ISongUseCase> m_song_usecase;
    };

    class SongIDEndpoint : public Endpoint<Request, Response> {
    public:
        SongIDEndpoint(std::shared_ptr<ISongUseCase> song_usecase);

        virtual Response Get(const Request& request) {
            return Response();
        }
    private:
        std::shared_ptr<ISongUseCase> m_song_usecase;
    };

    std::shared_ptr<ISongUseCase> m_song_usecase;
    SongEndpoint m_song_endpoint;
    SongIDEndpoint m_song_id_endpoint;
};

}  // namespace music_share

#endif  // MUS_MUSINTERNAL_MUSCONTROLLER_SongCONTROLLER_H_
