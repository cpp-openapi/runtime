#include "typefactory.h"

#include "beastclient.h"
#include "curlppclient.h"

std::shared_ptr<IClient> TypeFactory::NewClient(ClientConfig cfg)
{
    //std::shared_ptr<IClient> ret  = std::make_shared<BeastClient>(cfg);
    std::shared_ptr<CurlPPClient> ret = std::make_shared<CurlPPClient>(cfg);
    ret->SetDebug(true);
    return ret;
}