#pragma once
// #include "jsonopenapi.h"
#include "client.h"

class TypeFactory
{
public:
    static std::shared_ptr<IClient> NewClient(ClientConfig cfg);
};