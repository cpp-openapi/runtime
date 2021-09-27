#pragma once

#include <string>
#include <jsonopenapi.h>
#include <memory>
#include <optional>

class Error 
{
public:
    std::optional<int> code;
    std::optional<std::string> message;
    void SerializeJSON(std::shared_ptr<Json> j) const;
    void DeserializeJSON(std::shared_ptr<Json> j);
};