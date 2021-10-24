#include "openapi_rapidjson2.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

void RapidJson2::Parse(const std::string & data)
{
    this->_j.Parse(data.c_str());
}

bool RapidJson2::HasKey(const std::string &key) const
{
    return this->_j.HasMember(key.c_str());
}

std::string RapidJson2::ToString()
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    _j.Accept(writer);
    return std::string(buffer.GetString());
}