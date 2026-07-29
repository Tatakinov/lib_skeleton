#ifndef LIB_SKELETON_SORAKADO_H_
#define LIB_SKELETON_SORAKADO_H_

#include "lib_skeleton/base/request.h"
#include "lib_skeleton/base/response.h"

namespace lib_skeleton::sorakado {
    using Request = base::Request<"SORAKADO", "0.1", "Command", "Argument">;
    using Response = base::Response<"SORAKADO", "0.1", "Result", "Value">;
}

#endif // LIB_SKELETON_SORAKADO_H_
