#include "typefactory.h"
#include <iostream>
#include "find_todo.h"
#include "todoclient.h"

FindTodoResponse todoservice::FindTodos(FindTodosParams params)
{
    FindTodoResponse result;
    std::shared_ptr<IOASClientRequest> cri = std::make_shared<ClientRequestImpl>();
    params.WriteParams(cri);
    
    cri->SetHeaderParam("x-todolist-token", std::string("example token"));
    cri->SetMethod("GET");

    ClientResponseImpl respRet;

    Header h = cri->GetHeaderParam();
    //std::cout << h.size() << std::endl;
    _cli->MakeRequest(*cri, respRet);

    result.data = respRet.GetBody();
    result.code = respRet.GetCode();

    result.SetPayload(respRet.GetBody());
    return result;
}

void FindTodosParams::WriteParams(std::shared_ptr<IOASClientRequest> req){
    if (this->limit.has_value()){
        req->SetQueryParam<int>("limit", this->limit.value());
    }
    if (this->since.has_value()){
        req->SetQueryParam<int>("since", this->since.value());
    }
}

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