#pragma once

#include <string>
// #include <jsonopenapi.h>
#include <memory>
#include <optional>
#include "settings.h"

class Item
{
public:
    std::optional<int> id;
    std::optional<std::string> description;
    std::optional<bool> completed;
    OPENAPI_SERILIZATION_FUNCS_DECLARE
};