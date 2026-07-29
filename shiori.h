#ifndef LIB_SKELETON_SHIORI_H_
#define LIB_SKELETON_SHIORI_H_

#include "lib_skeleton/base/request.h"
#include "lib_skeleton/base/response.h"

namespace lib_skeleton::shiori {
    using Request = base::Request<"SHIORI", "3.0", "ID", "Reference">;
    using Response = base::Response<"SHIORI", "3.0", "Value", "Reference">;
}

#endif // LIB_SKELETON_SHIORI_H_
