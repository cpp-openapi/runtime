#pragma once

#include <string>
#include <jsonopenapi.h>
#include <memory>
#include <optional>

class Item
{
public:
    std::optional<int> id;
    std::optional<std::string> description;
    std::optional<bool> completed;

    void SerializeJSON(std::shared_ptr<Json> j) const;
    void DeserializeJSON(std::shared_ptr<Json> j);
};