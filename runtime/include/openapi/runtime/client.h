#pragma once

// middleware of different http clients

#include <string>
#include "openapi/runtime/request.h"
#include "openapi/runtime/response.h"
#include <future>

struct ClientConfig
{
    std::string Host;
    std::string Port;
    std::string BasePath;
};

class IClient
{
public:
    // TODO: change return
    IClient(ClientConfig cfg): _cfg(cfg) {};
    ClientConfig _cfg;
    virtual std::future<std::shared_ptr<IOASClientResponse>> Do(const std::shared_ptr<IOASClientRequest> req) = 0;
};