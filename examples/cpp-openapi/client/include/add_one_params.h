#pragma once

#include "item.h"
#include "openapi/runtime/request.h"
#include <optional>

struct AddOneParams
{
    static std::string const ContentType;
    static std::string const PathPattern;
    static std::string const Method;

    std::optional<Item> Body;
    void WriteParams(std::shared_ptr<IOASClientRequest> req) const;
};