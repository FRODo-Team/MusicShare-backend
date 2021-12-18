#include "mus-delivery/handler/playlisthandler.h"

#include <cstring>
#include <ranges>

#include "http/server/router.h"
#include "http/common.h"
#include "serializer.h"

namespace music_share::delivery {

PlaylistHandler::PlaylistHandler(IPlaylistUseCase& usecase) 
    : m_usecase(usecase) {}

void PlaylistHandler::Config(http::server::router::Router& router) {
    std::string prefix = "/api/v1/users/:id([0-9]+)/playlists";

    router.GET(http::server::router::Route(
        prefix,
        [this](auto, auto params) {
            auto body = GetByAuthor(::atoi(params["id"].c_str()));

            http::common::Response response;
            response.set(http::common::header::content_type,
                         "application/json");
            response.body() = nlohmann::json(body).dump();

            return response;
        }
    ));

    router.POST(http::server::router::Route(
        prefix,
        [this, prefix](http::common::Request request, auto params) {
            uint32_t playlist_id = CreatePlaylist(
                ::atoi(params["id"].c_str()),
                nlohmann::json::parse(request.body())
                    .template get<PlaylistRequestDTO>()
            );

            http::common::Response response;
            response.result(http::common::status::created);
            response.set(http::common::header::location,
                         prefix + "/" + std::to_string(playlist_id));

            return response;
        }
    ));

    router.GET(http::server::router::Route(
        prefix + "/:pid([0-9]+)",
        [this](auto, auto params) {
            auto body = GetById(
                ::atoi(params["id"].c_str()),
                ::atoi(params["pid"].c_str())
            );

            http::common::Response response;
            response.set(http::common::header::content_type,
                         "application/json");
            response.body() = nlohmann::json(body).dump();

            return response;
        }
    ));

    router.DELETE(http::server::router::Route(
        prefix + "/:pid([0-9]+)",
        [this](auto, auto params) {
            DeleteById(
                ::atoi(params["id"].c_str()),
                ::atoi(params["pid"].c_str())
            );

            http::common::Response response;
            response.result(http::common::status::no_content);

            return response;
        }
    ));

    router.GET(http::server::router::Route(
        prefix + "/:pid([0-9]+)/songs",
        [this](auto, auto params) {
            auto body = GetSongsById(
                ::atoi(params["id"].c_str()),
                ::atoi(params["pid"].c_str())
            );

            http::common::Response response;
            response.set(http::common::header::content_type,
                         "application/json");
            response.body() = nlohmann::json(body).dump();

            return response;
        }
    ));

    router.POST(http::server::router::Route(
        prefix + "/:pid([0-9]+)/songs",
        [this, prefix](http::common::Request request, auto params) {
            AddSongById(
                ::atoi(params["id"].c_str()),
                ::atoi(params["pid"].c_str()),
                nlohmann::json::parse(request.body())
                    .template get<PlaylistSongRequestDTO>()
            );

            http::common::Response response;
            return response;
        }
    ));

    router.DELETE(http::server::router::Route(
        prefix + "/:pid([0-9]+)/songs/:sid([0-9]+)",
        [this, prefix](http::common::Request request, auto params) {
            RemoveSongById(
                ::atoi(params["id"].c_str()),
                ::atoi(params["pid"].c_str()),
                ::atoi(params["sid"].c_str())
            );

            http::common::Response response;
            response.result(http::common::status::no_content);
            return response;
        }
    ));
}

std::vector<PlaylistResponseDTO>
PlaylistHandler::GetByAuthor(uint32_t author_id) {
    return m_usecase.GetByUserId(author_id);
}

uint32_t
PlaylistHandler::CreatePlaylist(uint32_t author_id,
                                const PlaylistRequestDTO& request) {
    return m_usecase.Create(author_id, request);
}

PlaylistResponseDTO
PlaylistHandler::GetById(uint32_t author_id, uint32_t playlist_id) {
    return m_usecase.GetById(playlist_id);
}

void
PlaylistHandler::DeleteById(uint32_t author_id, uint32_t playlist_id) {
    return m_usecase.DeleteById(author_id, playlist_id);
}

std::vector<uint32_t>
PlaylistHandler::GetSongsById(uint32_t author_id, uint32_t playlist_id) {
    return m_usecase.GetSongs(playlist_id);
}

void
PlaylistHandler::AddSongById(uint32_t author_id, uint32_t playlist_id,
                             const PlaylistSongRequestDTO& request) {
    return m_usecase.AddSongById(request, playlist_id, author_id);
}

void
PlaylistHandler::RemoveSongById(uint32_t author_id, uint32_t playlist_id,
                                uint32_t song_id) {
    return m_usecase.DeleteSongById(song_id, playlist_id, author_id);
}

}  // namespace music_share::delivery
