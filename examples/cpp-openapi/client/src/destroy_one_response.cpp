#include "destroy_one_response.h"

#include "typefactory.h"
#include <iostream>


void DestroyOneResponse::ReadResponse(std::shared_ptr<IOASClientResponse> resp)
{
    this->Code = resp->GetCode();

    std::string body = resp->GetBody();
    if (body.size() == 0){
        return;
    }
    std::shared_ptr<Json> j = TypeFactory::NewJson();
    j->SetJson(body);    
    this->Payload = Json::Get<Error>(j);
}

std::ostream& operator<<(std::ostream& os, const DestroyOneResponse& resp){
    std::shared_ptr<Json> j = TypeFactory::NewJson();
    if(resp.Payload.has_value())
    {
        Json::ToJson(j, resp.Payload.value());
    }
    os << "[" << resp.Code << "]: " << j->ToString();
    return os;
}