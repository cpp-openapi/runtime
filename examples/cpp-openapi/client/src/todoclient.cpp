
#include "todoclient.h"
#include "request.h"

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