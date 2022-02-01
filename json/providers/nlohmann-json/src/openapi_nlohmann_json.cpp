#include "openapi/json/nlohmann.h"

#include "openapi/runtime/strconv.h"

bool NlohmannJson::HasKey(const openapi::string_t &key) const
{
    return this->_j.contains(openapi::ToStdString(key)); // TODO: wchar to char
}

void NlohmannJson::Parse(const openapi::string_t &data)
{
    this->_j = nlohmann::json::parse(openapi::ToStdString(data));
}

openapi::string_t NlohmannJson::ToString() const
{
    return openapi::StringT(this->_j.dump().c_str());
}