#pragma once
// #include "jsonopenapi.h"
#include "openapi/runtime/client.h"

class TypeFactory
{
public:
    static std::shared_ptr<IClient> NewClient(ClientConfig cfg);
};