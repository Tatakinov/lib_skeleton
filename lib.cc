#include "lib.h"

#include "sstp/request.h"
#include "sstp/response.h"
#include "util.h"

bool __load(std::string path) {
    return true;
}

bool __unload() {
    return true;
}

std::string __request(std::string request) {
    sstp::Request req = sstp::Request::parse(request);
    sstp::Response res{204, "No Content", "SAORI/1.0"};
    return res;
}
