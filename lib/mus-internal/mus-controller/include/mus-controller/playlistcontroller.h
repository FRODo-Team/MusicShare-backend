#ifndef MUS_MUSINTERNAL_MUSCONTROLLER_PLAYLISTCONTROLLER_H_
#define MUS_MUSINTERNAL_MUSCONTROLLER_PLAYLISTCONTROLLER_H_

#include "mus-controller/endpoint.h"

#include <memory>  // std::shared_ptr

#include "mus-dto/playlist_request_dto.h"  // music_share::PlaylistRequestDTO
#include "mus-dto/playlist_response_dto.h"  // music_share::PlaylistRequestDTO
#include "mus-usecase/playlist_use_case.h"  // music_share::PlaylistUseCase
#include "mus-controller/request.h"
#include "mus-controller/response.h"

namespace music_share {

class PlaylistController {
public:
    using Request = Request<PlaylistRequestDTO>;
    using Response = Response<PlaylistResponseDTO>;

    PlaylistController();
    ~PlaylistController() = default;

    Response Playlist(const Request& response) {
        return m_playlist_endpoint(response);
    }
    Response PlaylistID(const Request& response) {
        return m_playlist_id_endpoint(response);
    }
private:
    class PlaylistEndpoint : public Endpoint<Request, Response> {
    public:
        PlaylistEndpoint(std::shared_ptr<IPlaylistUseCase> playlist_usecase);

        virtual Response Get(const Request& request) {
            return Response();
        }
        virtual Response Post(const Request& request) {
            return Response();
        }
    private:
        std::shared_ptr<IPlaylistUseCase> m_playlist_usecase;
    };

    class PlaylistIDEndpoint : public Endpoint<Request, Response> {
    public:
        PlaylistIDEndpoint(std::shared_ptr<IPlaylistUseCase> playlist_usecase);

        virtual Response Get(const Request& request) {
            return Response();
        }
        virtual Response Delete(const Request& request) {
            return Response();
        }
    private:
        std::shared_ptr<IPlaylistUseCase> m_playlist_usecase;
    };

    class PlaylistIDSongEndpoint : public Endpoint<Request, Response> {
    public:
        PlaylistIDSongEndpoint(std::shared_ptr<IPlaylistUseCase> playlist_usecase);

        virtual Response Get(const Request& request) {
            return Response();
        }
        virtual Response Post(const Request& request) {
            return Response();
        }
        virtual Response Delete(const Request& request) {
            return Response();
        }
    private:
        std::shared_ptr<IPlaylistUseCase> m_playlist_usecase;
    };

    std::shared_ptr<IPlaylistUseCase> m_playlist_usecase;
    PlaylistEndpoint m_playlist_endpoint;
    PlaylistIDEndpoint m_playlist_id_endpoint;
};

}  // namespace music_share

#endif  // MUS_MUSINTERNAL_MUSCONTROLLER_PLAYLISTCONTROLLER_H_
