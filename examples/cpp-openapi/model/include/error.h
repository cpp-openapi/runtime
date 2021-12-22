#pragma once

#include <string>
#include <memory>
#include <optional>
#include "settings.h"

class Error 
{
public:
    std::optional<int> code;
    std::optional<std::string> message;
    OPENAPI_JSON_CONVERT_FUNCS_DECLARE
};