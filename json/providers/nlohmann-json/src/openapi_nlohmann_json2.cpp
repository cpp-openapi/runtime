#include "openapi_nlohmann_json2.h"

bool NlohmannJson2::HasKey(const std::string &key) const
{
    return this->_j.contains(key);
}

void NlohmannJson2::Parse(const std::string &data)
{
    this->_j = nlohmann::json::parse(data);
}

std::string NlohmannJson2::ToString(){
    return this->_j.dump();
}