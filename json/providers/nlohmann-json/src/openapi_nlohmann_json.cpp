#include "openapi_nlohmann_json.h"

bool NlohmannJson::HasKey(const std::string &key) const
{
    return this->_j.contains(key);
}

void NlohmannJson::Parse(const std::string &data)
{
    this->_j = nlohmann::json::parse(data);
}

std::string NlohmannJson::ToString() const{
    return this->_j.dump();
}