#pragma once

#include "item.h"
#include "request.h"
#include <optional>

struct AddOneParams
{
    std::optional<Item> Body;
    void WriteParams(std::shared_ptr<IOASClientRequest> req);
};