#include "openapi/runtime/auth.h"

AuthInfoWriter APIAuth(std::string key, std::string val)
{
    return [=](std::shared_ptr<IOASClientRequest> req){
        req->SetHeaderParam(key,val);
    };
}