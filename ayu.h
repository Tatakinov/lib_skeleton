#ifndef AYU_H_
#define AYU_H_

#include "base/request.h"
#include "base/response.h"

namespace ayu {
    const char protocol_name[] = "AYU";
    const char protocol_version[] = "0.9";
    const char request_value[] = "Command";
    const char request_arg[] = "Argument";
    const char response_value[] = "Result";
    const char response_arg[] = "Value";
    typedef base::Request<protocol_name, protocol_version, request_value, request_arg> Request;
    typedef base::Response<protocol_name, protocol_version, response_value, response_arg> Response;
}

#endif // AYU_H_
