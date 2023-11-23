#ifndef SSTP_RESPONSE_H_
#define SSTP_RESPONSE_H_

#include <regex>
#include <sstream>
#include <string>

#include "base/header.h"

namespace base {

    template<const char *protocol_name, const char *protocol_version, const char *value, const char *arg>
        class Response {
            public:
                Response() : code_(), status_(), header_() {}
                Response(int code, const char *status) : code_(code), status_(status), header_() {}
                ~Response() {}
                static Response parse(std::string str) {
                    auto result = std::remove_if(str.begin(), str.end(),
                            [](int ch) {return ch == '\x0d';}
                    );
                    str.erase(result, str.end());
                    std::istringstream iss(str);
                    return parse(iss);
                }
                static Response parse(std::istringstream& iss) {
                    Response ret;
                    std::string line;
                    getline(iss, line, '\x0a');
                    decltype(line)::size_type pos    = line.find(' ');
                    if (pos == decltype(line)::npos) {
                        return ret;
                    }
                    // assert protocol name
                    // line.substr(0, pos);
                    std::string protocol = line.substr(0, pos);
                    std::string pattern;
                    pattern << protocol_name << R"(/\d+\.\d+)";
                    if (!regex_match(protocol, std::regex(pattern.str()))) {
                        return ret;
                    }
                    line    = line.substr(pos + 1);
                    pos    = line.find(' ');
                    if (pos == decltype(line)::npos) {
                        return ret;
                    }
                    ret.code_ = std::atoi(line.substr(0, pos).c_str());
                    ret.status_ = line.substr(pos + 1);
                    ret.header_ = Header::parse(iss);
                    return ret;
                }
                int getStatusCode() { return code_; }
                std::string getStatus() { return status_; }
                optional& operator[](std::string key) {
                    return header_[key];
                }
                optional& operator()() {
                    return header_[value];
                }
                optional& operator()(size_t index) {
                    std::ostringstream oss;
                    oss << arg << index;
                    return header_[oss.str()];
                }
                operator std::string() const {
                    std::ostringstream oss;
                    oss << protocol_name << "/" << protocol_version << " " << code_ << " " << status_ << "\x0d\x0a";
                    oss << static_cast<std::string>(header_);
                    oss << "\x0d\x0a";
                    return oss.str();
                }
            private:
                int code_;
                std::string status_;
                Header header_;
        };

}

#endif // SSTP_RESPONSE_H_
