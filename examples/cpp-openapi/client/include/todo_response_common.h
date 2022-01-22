#pragma once

#include "openapi/runtime/response.h"
#include "typefactory.h"
#include "openapi/runtime/runtime_types.h"
#include <memory>

template <typename R>
void ReadResponseCommon(R &res, std::shared_ptr<IOASClientResponse> resp)
{
    res.Code = resp->GetCode();

    using U = typename remove_optional<decltype(res.Payload)>::type;
    if constexpr (!std::is_same<decltype(res.Payload), EmptyPayload>::value
    &&  !std::is_same<U, EmptyPayload>::value)
    {
        std::string body = resp->GetBody();
        if (body.size() == 0){
            return;
        }
        res.Payload = Json::Deserialize<U>(openapi::StringT(body.c_str()));
    }
}