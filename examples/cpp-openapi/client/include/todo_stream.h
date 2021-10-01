#pragma once


#include <iostream>
#include <string>

template<typename R>
std::ostream& WriteResponseToStream(std::ostream& os, const R & resp)
{

    std::string payloadStr = "";
    using U = typename remove_optional<decltype(resp.Payload)>::type;
    if constexpr (!std::is_same<decltype(resp.Payload), EmptyPayload>::value
        &&  !std::is_same<U, EmptyPayload>::value)
    {
        std::shared_ptr<Json> j = TypeFactory::NewJson();
        if(resp.Payload.has_value())
        {
            Json::ToJson(j, resp.Payload.value());
        }
        payloadStr = j->ToString();
    }
    os << "[" << resp.Code << "]: " << payloadStr;
    return os;
}