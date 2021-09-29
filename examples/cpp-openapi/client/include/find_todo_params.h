#pragma once

#include <optional>
#include <memory>
#include "request.h"

struct FindTodosParams
{
    std::optional<int> limit;
    std::optional<int> since;
    void WriteParams(std::shared_ptr<IOASClientRequest> req);
};