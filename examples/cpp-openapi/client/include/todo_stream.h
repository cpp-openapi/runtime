#pragma once

#include <iostream>
#include <string>

template<typename R>
std::ostream& WriteResponseToStream(std::ostream& os, const R & resp)
{

    openapi::string_t payloadStr{};
    using U = typename remove_optional<decltype(resp.Payload)>::type;
    if constexpr (!std::is_same<decltype(resp.Payload), EmptyPayload>::value
        &&  !std::is_same<U, EmptyPayload>::value)
    {
        if(resp.Payload.has_value())
        {
            payloadStr = Json::Serialize(resp.Payload);
        }
    }
    os << "[" << resp.Code << "]: " << openapi::ToStdString(payloadStr); // TODO: wstream?
    return os;
}