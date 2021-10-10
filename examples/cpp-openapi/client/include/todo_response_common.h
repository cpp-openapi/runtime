#pragma once

#include "response.h"
#include "typefactory.h"
#include "runtime_types.h"
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
        std::shared_ptr<Json> j = TypeFactory::NewJson();
        j->SetJson(body);
        res.Payload = Json::Get<U>(j);
    }
}