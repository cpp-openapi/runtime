#pragma once

#include <string>
#include <memory>
#include <optional>
#include "settings.h"

class Item
{
public:
    std::optional<int> id;
    std::optional<std::string> description;
    std::optional<bool> completed;
    OPENAPI_JSON_CONVERT_FUNCS_DECLARE
};