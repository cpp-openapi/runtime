#pragma once

#include "request.h"
#include "response.h"
#include "error.h"
#include <optional>
#include <memory>

struct DestroyOneParams
{
    static std::string const ContentType;
    static std::string const PathPattern;
    static std::string const Method;

    // path param
    std::optional<int> id;
    void WriteParams(std::shared_ptr<IOASClientRequest> req);
};

struct DestroyOneResponse
{
    std::optional<Error> Payload;
    int Code;
    void ReadResponse(std::shared_ptr<IOASClientResponse> resp);
    friend std::ostream& operator<<(std::ostream& os, const DestroyOneResponse& resp);
};