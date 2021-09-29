#pragma once

#include "response.h"
#include "error.h"
#include <optional>
#include <memory>


struct DestroyOneResponse
{
    std::optional<Error> Payload;
    int Code;
    void ReadResponse(std::shared_ptr<IOASClientResponse> resp);
    friend std::ostream& operator<<(std::ostream& os, const DestroyOneResponse& resp);
};