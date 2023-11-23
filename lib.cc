#include "lib.h"

#include "saori.h"
#include "util.h"

bool __load(std::string path) {
    return true;
}

bool __unload() {
    return true;
}

std::string __request(std::string request) {
    saori::Request req = saori::Request::parse(request);
    // if (!req["Argument0"]) { と等価
    if (!req(0)) {
        saori::Response res{204, "No Content"};
        return res;
    }
    saori::Response res{200, "OK"};
    if (req["Charset"]) {
        res["Charset"]  = req["Charset"].value();
    }

    // res["Result"]   = req["Argument0"].value();と等価
    res() = req(0).value();
    return res;
}
