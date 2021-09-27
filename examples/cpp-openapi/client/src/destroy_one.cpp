#include "destroy_one.h"

#include "typefactory.h"
#include "todoclient.h"

std::string const DestroyOneParams::ContentType = "application/io.goswagger.examples.todo-list.v1+json";
std::string const DestroyOneParams::Method = "DELETE";
std::string const DestroyOneParams::PathPattern = "/{id}";

DestroyOneResponse todoservice::DestroyOne(DestroyOneParams params)
{
    DestroyOneResponse result;
    std::shared_ptr<IOASClientRequest> cri = std::make_shared<ClientRequestImpl>();
    params.WriteParams(cri);
    cri->SetHeaderParam("x-todolist-token", std::string("example token"));

    std::shared_ptr<IOASClientResponse> resp =  std::make_shared<ClientResponseImpl>();

    _cli->MakeRequest(*cri, *resp);

    result.ReadResponse(resp);
    
    return result;
}


void DestroyOneParams::WriteParams(std::shared_ptr<IOASClientRequest> req)
{
    req->SetHeaderParam("Content-Type", DestroyOneParams::ContentType);
    req->SetMethod(DestroyOneParams::Method);
    req->SetPathPattern(DestroyOneParams::PathPattern);
    if (this->id.has_value())
    {
        req->SetPathParam("id", this->id.value());
    }
}

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