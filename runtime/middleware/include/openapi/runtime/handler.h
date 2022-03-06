#pragma once

#include "openapi/runtime/request.h"
#include "openapi/runtime/response.h"

namespace openapi{

class IHttpHandler
{
    // process req and populate resp
    virtual void HandleHttp(IOASClientRequest & req, IOASClientResponse &resp) = 0;
};

} // namespace openapi