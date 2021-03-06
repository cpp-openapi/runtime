#pragma once

#include <string>
#include <memory>
#include <optional>
#include "settings.h"
#include "openapi/runtime/string.h"
#include "openapi/runtime/type_mangle.h"

class Item
{
public:
    std::optional<int> id;
    std::optional<openapi::string_t> description;
    std::optional<bool> completed;
    OPENAPI_JSON_CONVERT_FUNCS_DECLARE
};