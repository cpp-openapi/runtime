#include "add_one.h"
#include "typefactory.h"
#include "todoclient.h"

AddOneResponse todoservice::AddOne(AddOneParams params)
{
    AddOneResponse result;
    std::shared_ptr<IOASClientRequest> cri = std::make_shared<ClientRequestImpl>();
    params.WriteParams(cri);
    
    cri->SetHeaderParam("x-todolist-token", std::string("example token"));
    cri->SetHeaderParam("Content-Type", std::string("application/io.goswagger.examples.todo-list.v1+json"));
    cri->SetMethod("POST");

    ClientResponseImpl respRet;

    _cli->MakeRequest(*cri, respRet);

    //result.data = respRet.GetBody();
    result.Code = respRet.GetCode();

    result.SetPayload(respRet.GetBody());
    return result;
}


void AddOneParams::WriteParams(std::shared_ptr<IOASClientRequest> req)
{
    if (this->Body.has_value())
    {
        std::shared_ptr<Json> j = TypeFactory::NewJson();
        Json::ToJson(j, this->Body.value());
        req->SetBodyParam(j->ToString());
        //std::cout << "debug body: " << req->GetBody() << std::endl;
    }
}

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