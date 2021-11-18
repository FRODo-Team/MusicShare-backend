#ifndef MUS_MUSINTERNAL_MUSCONTROLLER_ENDPOINT_H_
#define MUS_MUSINTERNAL_MUSCONTROLLER_ENDPOINT_H_

namespace music_share {

template <typename Request, typename Response>
class Endpoint {
public:
    virtual ~Endpoint() = default;

    Response operator()(const Request& request) {
        return Response();
    }

    virtual Response Get(const Request& request) {
        return Response();
    }
    virtual Response Post(const Request& request) {
        return Response();
    }
    virtual Response Patch(const Request& request) {
        return Response();
    }
    virtual Response Delete(const Request& request) {
        return Response();
    }
};

}  // namespace music_share 

#endif  // MUS_MUSINTERNAL_MUSCONTROLLER_ENDPOINT_H_
