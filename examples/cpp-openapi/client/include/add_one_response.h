#pragma once

#include "item.h"
#include <optional>
#include "openapi/runtime/response.h"


struct AddOneResponse
{
    std::optional<Item> Payload;
    int Code;
    void ReadResponse(std::shared_ptr<IOASClientResponse> resp);
    friend std::ostream& operator<<(std::ostream& os, const AddOneResponse& resp);
};