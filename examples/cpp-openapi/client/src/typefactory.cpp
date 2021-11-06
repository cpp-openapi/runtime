#include "typefactory.h"

#include "openapi_nlohmann_json.h"
#include "openapi_rapidjson.h"
#include "beastclient.h"
#include "curlppclient.h"

// std::shared_ptr<Json> TypeFactory::NewJson()
// {
//     return std::make_shared<NlohmannJson>();
//     //return std::make_shared<RapidJson>();
// }

std::shared_ptr<IClient> TypeFactory::NewClient(ClientConfig cfg)
{
    //std::shared_ptr<IClient> ret  = std::make_shared<BeastClient>(cfg);
    std::shared_ptr<CurlPPClient> ret = std::make_shared<CurlPPClient>(cfg);
    ret->SetDebug(true);
    return ret;
}