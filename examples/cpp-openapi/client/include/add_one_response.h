#pragma once

#include "item.h"
#include <optional>


struct AddOneResponse
{
    std::optional<Item> Payload;
    int Code;
    void SetPayload(std::shared_ptr<Json> j);
    void SetPayload(std::string data);
    friend std::ostream& operator<<(std::ostream& os, const AddOneResponse& resp);
};