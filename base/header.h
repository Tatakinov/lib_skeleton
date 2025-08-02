#ifndef SSTP_HEADER_H_
#define SSTP_HEADER_H_

#include <algorithm>
#include <sstream>
#include <string>
#include <unordered_map>

#include "base/optional.h"

namespace base {

class Header {
    public:
        Header() {}

        ~Header() {}

        static Header parse(std::string str) {
            auto result = std::remove_if(str.begin(), str.end(),
                    [](int ch) {return ch == '\x0d';}
            );
            str.erase(result, str.end());
            std::istringstream iss(str);
            return parse(iss);
        }

        static Header parse(std::istringstream& iss) {
            Header tmp;
            std::string header;
            while (std::getline(iss, header, '\x0a') && !header.empty()) {
                decltype(header)::size_type pos    = header.find(':');
                if (pos == decltype(header)::npos) {
                    continue;
                }
                std::string key = header.substr(0, pos);
                std::string value = header.substr(pos + 2);
                tmp[key] = value;
            }
            return tmp;
        }

        inline void remove(const std::string& key) {
            map_.erase(key);
        }

        inline optional& operator[](const std::string& key) { return map_[key]; }
        operator std::string() const {
            std::ostringstream oss;
            auto h = map_;
            // Charsetは他のヘッダより優先する
            if (h["Charset"]) {
                oss << "Charset: " << h["Charset"].value() << "\x0d\x0a";
            }
            for (auto& [k, v] : h) {
                if (k != "Charset" && v) {
                    oss << k << ": " << v.value() << "\x0d\x0a";
                }
            }
            return oss.str();
        }
    private:
        std::unordered_map<std::string, optional> map_;
};

}

#endif // SSTP_HEADER_H_
