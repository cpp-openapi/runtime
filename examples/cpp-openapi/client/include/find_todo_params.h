#pragma once

#include <optional>
#include <memory>
#include "openapi/runtime/request.h"

struct FindTodosParams
{
    static std::string const ContentType;
    static std::string const PathPattern;
    static std::string const Method;

    std::optional<int> limit;
    std::optional<int> since;
    void WriteParams(std::shared_ptr<IOASClientRequest> req) const;
};