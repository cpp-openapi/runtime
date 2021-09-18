
#include "todoclient.h"
#include "request.h"

//#include "openapi_nlohmann_json.h"
//#include "openapi_rapidjson.h"
#include "typefactory.h"
#include <iostream>

findTodoResponse todoservice::findTodos(findTodosParams params)
{
    findTodoResponse result;
    ClientRequestImpl cri;
    cri.SetHeaderParam("x-todolist-token",{"example token"});
    cri.SetMethod("GET");

    ClientResponseImpl respRet;

    _cli->MakeRequest(cri, respRet);

    result.data = respRet.GetBody();
    result.code = respRet.GetCode();

    // Try convert payload
    std::shared_ptr<Json> j = TypeFactory::NewJson();
    //std::shared_ptr<Json> j = std::make_shared<RapidJson>();
    j->SetJson(result.data);

    std::vector<Item> res = j->ToArray<Item>();
    result.payload = res;
    // std::vector<std::shared_ptr<Json>> res;
    // bool isArray = j->ToArray(res);
    // std::cout <<"is array: "<< isArray << " debug size: "<< res.size() << std::endl;
    for (auto& e : res) {
        std::cout <<"item: "<< e.id << " description: " << e.description <<std::endl;
        //std::shared_ptr<Json> ret = std::make_shared<NlohmannJson>();
        std::shared_ptr<Json> ret = TypeFactory::NewJson();
        e.to_json(ret); 
        std::cout << "deserialize: " << ret->ToString() << std::endl;
    }

    return result;
}