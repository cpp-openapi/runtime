#pragma once

#include <string>
#include <vector>
#include "item.h"
#include <iostream>
#include <optional>
#include "request.h"

struct FindTodosParams
{
    std::optional<int> limit;
    std::optional<int> since;
    void WriteParams(std::shared_ptr<IOASClientRequest> req);
};

struct FindTodoResponse
{
    std::string data;
    int code;
    std::optional<std::vector<Item>> Payload;
    void SetPayload(std::shared_ptr<Json> j);
    void SetPayload(std::string data);
    friend std::ostream& operator<<(std::ostream& os, const FindTodoResponse& resp);
};