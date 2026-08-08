#ifndef LIB_SKELETON_BASE_REQUEST_H_
#define LIB_SKELETON_BASE_REQUEST_H_

#include <regex>
#include <sstream>
#include <string>

#include "lib_skeleton/const_string.h"
#include "lib_skeleton/base/header.h"

namespace lib_skeleton::base {
    template<ConstString protocol_name, ConstString protocol_version, ConstString value, ConstString arg>
        class Request {
            private:
                inline static const std::regex proto_regex = std::regex(std::string(protocol_name.buf) + R"(/\d+\.\d+)");
            public:
                Request(std::string command) : command_(command), protocol_(std::string(protocol_name.buf) + "/" + protocol_version.buf), header_() {}
                ~Request() {}
                static Request parse(std::string str) {
                    auto result = std::remove_if(str.begin(), str.end(),
                            [](int ch) {return ch == '\x0d';}
                    );
                    str.erase(result, str.end());
                    std::istringstream iss(str);
                    return parse(iss);
                }
                static Request parse(std::istringstream& iss) {
                    Request ret;
                    std::string line;
                    getline(iss, line, '\x0a');
                    decltype(line)::size_type pos    = line.rfind(' ');
                    if (pos == decltype(line)::npos) {
                        return ret;
                    }
                    // assert protocol name
                    // line.substr(pos + 1)
                    std::string protocol = line.substr(pos + 1);
                    if (!regex_match(protocol, proto_regex)) {
                        return ret;
                    }
                    ret.command_    = line.substr(0, pos);
                    ret.protocol_   = protocol;
                    ret.header_     = Header::parse(iss);
                    return ret;
                }
                std::string getCommand() { return command_; }
                std::string getProtocol() { return protocol_; }
                optional& operator[](const std::string& key) {
                    return header_[key];
                }
                const optional& operator()() const {
                    return header_[value.buf];
                }
                optional& operator()() {
                    return header_[value.buf];
                }
                const optional& operator()(size_t index) const {
                    std::ostringstream oss;
                    oss << arg.buf << index;
                    return header_[oss.str()];
                }
                optional& operator()(size_t index) {
                    std::ostringstream oss;
                    oss << arg.buf << index;
                    return header_[oss.str()];
                }
                operator std::string() const {
                    std::ostringstream oss;
                    oss << command_ << " " << protocol_ << "\x0d\x0a";
                    oss << static_cast<std::string>(header_);
                    oss << "\x0d\x0a";
                    return oss.str();
                }

            private:
                std::string command_;
                std::string protocol_;
                Header header_;

                Request() : command_(), protocol_(), header_() {}
        };

}

#endif // LIB_SKELETON_BASE_REQUEST_H_
