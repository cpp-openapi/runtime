#include "openapi_rapidjson.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "strconv.h"

void RapidJson::Parse(const openapi::string_t & data)
{
    this->_j.Parse(openapi::ToStdString(data.c_str()).c_str());
}

bool RapidJson::HasKey(const openapi::string_t &key) const
{
    return this->_j.HasMember(openapi::ToStdString(key.c_str()).c_str());
}

openapi::string_t RapidJson::ToString() const
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    _j.Accept(writer);
    return openapi::StringT(buffer.GetString());
}