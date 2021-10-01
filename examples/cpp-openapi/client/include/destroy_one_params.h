#pragma once
#include "request.h"
#include <optional>
#include <memory>

struct DestroyOneParams
{
    static std::string const ContentType;
    static std::string const PathPattern;
    static std::string const Method;

    // path param
    std::optional<int> id;
    void WriteParams(std::shared_ptr<IOASClientRequest> req) const;
};