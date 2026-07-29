#ifndef LIB_SKELETON_PLUGIN_H_
#define LIB_SKELETON_PLUGIN_H_

#include "lib_skeleton/base/request.h"
#include "lib_skeleton/base/response.h"

namespace lib_skeleton::plugin {
    using Request = base::Request<"PLUGIN", "2.0", "ID", "Reference">;
    using Response = base::Response<"PLUGIN", "2.0", "Event", "Reference">;
}

#endif // LIB_SKELETON_PLUGIN_H_
