#pragma once
#include <string>
#include <vector>
#include "item.h"
#include <iostream>
#include <optional>
#include "openapi/runtime/response.h"

struct FindTodoResponse
{
    // std::string data;
    int Code;
    std::optional<std::vector<Item>> Payload;
    void ReadResponse(std::shared_ptr<IOASClientResponse> resp);
    friend std::ostream& operator<<(std::ostream& os, const FindTodoResponse& resp);
};