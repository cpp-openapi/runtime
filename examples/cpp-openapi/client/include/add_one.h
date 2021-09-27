#pragma once
#include "item.h"
#include "request.h"
#include <optional>

struct AddOneParams
{
    std::optional<Item> Body;
    void WriteParams(std::shared_ptr<IOASClientRequest> req);
};

struct AddOneResponse
{
    std::optional<Item> Payload;
    int Code;
    void SetPayload(std::shared_ptr<Json> j);
    void SetPayload(std::string data);
    friend std::ostream& operator<<(std::ostream& os, const AddOneResponse& resp);
};