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
        if(resp.Payload.has_value())
        {
            Json j = Json::Serialize(resp.Payload.value());
            payloadStr = j.ToString();
        }
    }
    os << "[" << resp.Code << "]: " << payloadStr;
    return os;
}