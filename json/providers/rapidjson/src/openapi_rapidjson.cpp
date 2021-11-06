#include "openapi_rapidjson.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

void RapidJson::Parse(const std::string & data)
{
    this->_j.Parse(data.c_str());
}

bool RapidJson::HasKey(const std::string &key) const
{
    return this->_j.HasMember(key.c_str());
}

std::string RapidJson::ToString() const
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    _j.Accept(writer);
    return std::string(buffer.GetString());
}