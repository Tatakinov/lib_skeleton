#ifndef LIB_SKELETON_BASE_RESPONSE_H_
#define LIB_SKELETON_BASE_RESPONSE_H_

#include <regex>
#include <sstream>
#include <string>

#include "lib_skeleton/base/header.h"

namespace lib_skeleton::base {
    template<ConstString protocol_name, ConstString protocol_version, ConstString value, ConstString arg>
        class Response {
            private:
                inline static const std::regex proto_regex = std::regex(std::string(protocol_name.buf) + R"(/\d+\.\d+)");
            public:
                Response(int code, std::string status) : code_(code), status_(status), protocol_(std::string(protocol_name.buf) + "/" + protocol_version.buf), header_() {}
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
                    if (!regex_match(protocol, proto_regex)) {
                        return ret;
                    }
                    line    = line.substr(pos + 1);
                    pos    = line.find(' ');
                    if (pos == decltype(line)::npos) {
                        return ret;
                    }
                    ret.code_ = std::atoi(line.substr(0, pos).c_str());
                    ret.status_ = line.substr(pos + 1);
                    ret.protocol_   = protocol;
                    ret.header_ = Header::parse(iss);
                    std::string tmp;
                    while (std::getline(iss, tmp, '\x0a')) {
                        if (tmp.empty()) {
                            break;
                        }
                        ret.content_.append(tmp);
                        ret.content_.append("\x0a");
                    }
                    return ret;
                }
                int getStatusCode() { return code_; }
                std::string getStatus() { return status_; }
                std::string getProtocol() { return protocol_; }
                optional& operator[](const std::string& key) {
                    return header_[key];
                }
                optional& operator()() {
                    return header_[value.buf];
                }
                optional& operator()(size_t index) {
                    std::ostringstream oss;
                    oss << arg.buf << index;
                    return header_[oss.str()];
                }
                std::string getContent() const {
                    return content_;
                }
                operator std::string() const {
                    std::ostringstream oss;
                    oss << protocol_ << " " << code_ << " " << status_ << "\x0d\x0a";
                    oss << static_cast<std::string>(header_);
                    oss << "\x0d\x0a";
                    if (!content_.empty()) {
                        oss << content_ << "\x0d\x0a";
                        oss << "\x0d\x0a";
                    }
                    return oss.str();
                }
            private:
                int code_;
                std::string status_;
                std::string protocol_;
                Header header_;
                std::string content_;

                Response() : code_(), status_(), protocol_(), header_() {}
        };

}

#endif // LIB_SKELETON_BASE_RESPONSE_H_
