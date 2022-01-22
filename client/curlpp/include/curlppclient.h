#pragma once
#include "openapi/runtime/client.h"

class CurlPPClient : public IClient
{
public:
    using IClient::IClient;
    std::future<std::shared_ptr<IOASClientResponse>> Do(const std::shared_ptr<IOASClientRequest> req) override;
    void SetDebug(bool debug);
private:
    bool _debug = false;

    std::shared_ptr<IOASClientResponse> doSync(const std::shared_ptr<IOASClientRequest> req);
};