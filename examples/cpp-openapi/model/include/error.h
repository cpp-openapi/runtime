#pragma once

#include <string>
// #include <jsonopenapi.h>
#include <memory>
#include <optional>
#include "settings.h"

class Error 
{
public:
    std::optional<int> code;
    std::optional<std::string> message;
    OPENAPI_SERILIZATION_FUNCS_DECLARE
};