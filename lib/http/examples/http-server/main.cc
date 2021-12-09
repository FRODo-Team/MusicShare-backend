#include <memory>
#include <set>
#include <iostream>

#include "http/server.h"
#include "http/common.h"

namespace http = boost::beast::http;
using namespace music_share::http::server;
using namespace music_share::http::common;
using namespace music_share::http::server::middleware;

class MyMW: public IMiddleware {
public:
    MyMW(RequestHandler handler) : IMiddleware(handler) {}
    ~MyMW() = default;

    Response operator()(const Request& r, const Parameters& params) {
        auto response = get_response(r, params);
        size_t query_start = r.target().find('?');
        auto qs = QueryString::fromString(r.target().substr(query_start + 1).to_string());
        for (const auto& [key, value]: qs.Entries()) {
            response.body() += key + " " + value + "\n";
        }
        auto [beg, end] = qs.GetAll("city");
        std::vector<std::string> cities;
        std::transform(beg, end, std::back_inserter(cities), [](auto it) { return it.second; });
        for (const auto& city: cities) {
            response.body() += city + " ";
        }
        response.body() += "\n";
        response.body() = response.body().data() + std::string("Hook!!!\n");
        return response;
    }
};

class MW1: public IMiddleware {
public:
    MW1(RequestHandler handler) : IMiddleware(handler) {}
    ~MW1() = default;

    Response operator()(const Request& r, const Parameters& params) {
        std::cout << "MW1 in\n";
        auto response = get_response(r, params);
        std::cout << "MW1 out\n";
        return response;
    }
};

class MW2: public IMiddleware {
public:
    MW2(RequestHandler handler) : IMiddleware(handler) {}
    ~MW2() = default;

    Response operator()(const Request& r, const Parameters& params) {
        std::cout << "MW2 in\n";
        auto response = get_response(r, params);
        std::cout << "MW2 out\n";
        return response;
    }
};

int main(void) {
    Server server("localhost", "8580");

    server.Router().Require(MiddlewareBuilder<InternalServerError>::Create());
    server.Router().Require(MiddlewareBuilder<MethodNotAllowed>::Create());
    server.Router().Require(MiddlewareBuilder<NotFound>::Create());

    server.Router().GET(
        router::Route(
            "/",
            [](auto, auto) {
                Response response;
                response.set(http::field::content_type, "text/plain");
                response.result(http::status::ok);
                response.body() = "Hello, Rostislav!\n";
                return response;
            }, {}
        )
    );
    server.Router().GET(
        router::Route(
            "/duuude",
            [](auto, auto) {
                Response response;
                response.set(http::field::content_type, "text/plain");
                response.result(http::status::ok);
                response.body() = "Hello, some Dude!\n";
                return response;
            }, {MiddlewareBuilder<MW1>::Create(), MiddlewareBuilder<MW2>::Create()}
        )
    );
    server.Router().GET(
        router::Route(
            "/duuude/:id([0-9]+)",
            [](auto, auto params) {
                Response response;
                response.set(http::field::content_type, "text/plain");
                response.result(http::status::ok);
                response.body() = "Hello, Dude #" + params["id"] + "!\n";
                return response;
            }, {}
        )
    );
    server.Router().GET(
        router::Route(
            "/duuude/:id([0-9]+)/bye",
            [](auto, auto params) {
                Response response;
                response.set(http::field::content_type, "text/plain");
                response.result(http::status::ok);
                response.body() = "Bye, Dude #" + params["id"] + "!\n";
                return response;
            }, { MiddlewareBuilder<MyMW>::Create() }
        )
    );
    server.Router().GET(
        router::Route(
            "/duuude/:id([0-9]+)/notbye",
            [](auto, auto params) {
                Response response;
                response.set(http::field::content_type, "text/plain");
                response.result(http::status::ok);
                response.body() = "Not bye, Dude #" + params["id"] + "!\n";
                return response;
            }, { MiddlewareBuilder<MyMW>::Create() }
        )
    );
    server.Router().GET(
        router::Route(
            "/duuude/:id([0-9]+)/notbye/:name(\\w+)",
            [](auto, auto params) {
                Response response;
                response.set(http::field::content_type, "text/plain");
                response.result(http::status::ok);
                response.body() = "Not bye, Dude #" + params["id"] + " " + params["name"] + "!\n";
                return response;
            }, { MiddlewareBuilder<MyMW>::Create() }
        )
    );

    server.Run();

    return 0;
}
