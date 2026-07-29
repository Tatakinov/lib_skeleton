#ifndef LIB_SKELETON_CONST_STRING_H_
#define LIB_SKELETON_CONST_STRING_H_

#include <algorithm>

namespace lib_skeleton {
    template<std::size_t n>
    struct ConstString {
        char buf[n + 1]{};
        constexpr ConstString(const char *s) {
            std::copy_n(s, n, buf);
        }
    };

    template<std::size_t n>
    ConstString(const char (&)[n]) -> ConstString<n - 1>;
}

#endif // LIB_SKELETON_CONST_STRING_H_
