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
    if (req["Arugment0"]) {
        sstp::Response res{"SAORI/1.0", 200, "OK"};
        res["Result"] = req["Argument0"].value();
        return res;
    }
    sstp::Response res{"SAORI/1.0", 204, "No Content"};
    return res;
}
