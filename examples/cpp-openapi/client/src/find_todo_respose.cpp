#include "find_todo_response.h"
#include "typefactory.h"

void FindTodoResponse::SetPayload(std::shared_ptr<Json> j)
{
    this->Payload = Json::Get<std::vector<Item>>(j);
}

void FindTodoResponse::SetPayload(std::string data)
{
    if (data.size() == 0){
        return;
    }
    std::shared_ptr<Json> j = TypeFactory::NewJson();
    j->SetJson(data);
    this->SetPayload(j);
}

std::ostream& operator<<(std::ostream& os, const FindTodoResponse& resp){
    std::shared_ptr<Json> j = TypeFactory::NewJson();
    if(resp.Payload.has_value())
    {
        Json::ToJson(j, resp.Payload.value());
    }
    os << "[" << resp.code << "]: " << j->ToString();
    return os;
}