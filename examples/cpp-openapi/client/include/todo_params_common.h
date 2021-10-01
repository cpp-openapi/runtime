#pragma once

#include "request.h"
#include <memory>

// P must be param type
template<typename P>
void WriteParamsCommon(const P &param, std::shared_ptr<IOASClientRequest> req)
{
    req->SetHeaderParam("Content-Type", P::ContentType);
    req->SetMethod(P::Method);
    req->SetPathPattern(P::PathPattern);
}