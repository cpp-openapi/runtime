#pragma once
#include <string>
#include <vector>
#include "item.h"
#include <iostream>
#include <optional>

struct FindTodoResponse
{
    std::string data;
    int code;
    std::optional<std::vector<Item>> Payload;
    void SetPayload(std::shared_ptr<Json> j);
    void SetPayload(std::string data);
    friend std::ostream& operator<<(std::ostream& os, const FindTodoResponse& resp);
};