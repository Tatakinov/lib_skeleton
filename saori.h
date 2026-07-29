#ifndef LIB_SKELETON_SAORI_H_
#define LIB_SKELETON_SAORI_H_

#include "lib_skeleton/base/request.h"
#include "lib_skeleton/base/response.h"

namespace lib_skeleton::saori {
    using Request = base::Request<"SAORI", "1.0", "unused", "Argument">;
    using Response = base::Response<"SAORI", "1.0", "Result", "Value">;
}

#endif // LIB_SKELETON_SAORI_H_
