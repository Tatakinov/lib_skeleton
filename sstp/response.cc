#include "response.h"

#include <cstdio>

namespace sstp {

Response::Response() : protocol_(), code_(), status_(), header_() {}
Response::Response(const char *protocol, int code, const char *status) : protocol_(protocol), code_(code), status_(status), header_() {}
Response::~Response() {}

Response Response::parse(std::string str) {
    auto result = std::remove_if(str.begin(), str.end(),
            [](int ch) {return ch == '\x0d';}
    );
    str.erase(result, str.end());
    return parse(std::istringstream(str));
}

Response Response::parse(std::istringstream iss) {
    Response tmp;
    std::string line;
    getline(iss, line, '\x0a');
    decltype(line)::size_type pos    = line.find(' ');
    if (pos == decltype(line)::npos) {
        return tmp;
    }
    tmp.protocol_ = line.substr(0, pos);
    line    = line.substr(pos + 1);

    pos    = line.find(' ');
    if (pos == decltype(line)::npos) {
        return tmp;
    }
    tmp.code_ = std::atoi(line.substr(0, pos).c_str());
    tmp.status_ = line.substr(pos + 1);
    tmp.header_ = Header::parse(iss);
    return tmp;
}

std::optional<std::string> Response::operator[](std::string key) {
    return header_[key];
}

}
