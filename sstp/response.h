#ifndef SSTP_RESPONSE_H_
#define SSTP_RESPONSE_H_

#include <sstream>
#include <string>

#include "sstp/header.h"

namespace sstp {

class Response {
    public:
        Response();
        Response(const char *protocol, int code, const char *status);
        ~Response();
        static Response parse(std::string str);
        static Response parse(std::istringstream iss);
        int getStatusCode() {return code_;}
        std::string getStatus() {return status_;}
        std::string getProtocol() {return protocol_;}
        void setStatusCode(int code) {code_ = code;}
        void setStatus(std::string status) {status_ = status;}
        void setProtocol(std::string protocol) {protocol_ = protocol;}
        template<typename T> void set(std::string key, T value) { header_.set(key, value); }
        std::optional<std::string> operator[](std::string key);
        operator std::string() const {
            std::ostringstream oss;
            oss << protocol_ << " " << code_ << " " << status_ << "\x0d\x0a";
            oss << static_cast<std::string>(header_);
            oss << "\x0d\x0a";
            return oss.str();
        }
    private:
        std::string protocol_;
        int code_;
        std::string status_;
        Header header_;
};

}

#endif // SSTP_RESPONSE_H_
