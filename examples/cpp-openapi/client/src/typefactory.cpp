#include "typefactory.h"

#ifdef OPENAPI_CLIENT_CURLPP
#include "curlppclient.h"
#elif defined(OPENAPI_CLIENT_BREAST)
#include "beastclient.h"
#endif

std::shared_ptr<IClient> TypeFactory::NewClient(ClientConfig cfg)
{
#ifdef OPENAPI_CLIENT_CURLPP
    std::shared_ptr<CurlPPClient> ret = std::make_shared<CurlPPClient>(cfg);
    ret->SetDebug(true);
#elif defined(OPENAPI_CLIENT_BREAST)
    std::shared_ptr<IClient> ret  = std::make_shared<BeastClient>(cfg);
#endif
    return ret;
}