#pragma once
#include "client.h"

class BeastClient : public IClient
{
public:
    using IClient::IClient;
    std::future<std::shared_ptr<IOASClientResponse>> Do(const std::shared_ptr<IOASClientRequest> req) override;

private:
    std::shared_ptr<IOASClientResponse> doSync(const std::shared_ptr<IOASClientRequest> req);
};