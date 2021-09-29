#include "add_one_response.h"
#include "typefactory.h"
#include <string>
#include <iostream>

void AddOneResponse::SetPayload(std::shared_ptr<Json> j)
{
    this->Payload = Json::Get<Item>(j);
}
void AddOneResponse::SetPayload(std::string data){
    if (data.size() == 0){
        return;
    }
    std::shared_ptr<Json> j = TypeFactory::NewJson();
    j->SetJson(data);
    this->SetPayload(j);
}

std::ostream& operator<<(std::ostream& os, const AddOneResponse& resp){
    std::shared_ptr<Json> j = TypeFactory::NewJson();
    if(resp.Payload.has_value())
    {
        Json::ToJson(j, resp.Payload.value());
    }
    os << "[" << resp.Code << "]: " << j->ToString();
    return os;
}