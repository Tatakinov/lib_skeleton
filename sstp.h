#ifndef LIB_SKELETON_SSTP_H_
#define LIB_SKELETON_SSTP_H_

#include "lib_skeleton/base/request.h"
#include "lib_skeleton/base/response.h"

namespace lib_skeleton::sstp {
    using Request = base::Request<"SSTP", "1.4", "Event", "Reference">;
    using Response = base::Response<"SSTP", "1.4", "Script", "unused">;
}

#endif // LIB_SKELETON_SSTP_H_
