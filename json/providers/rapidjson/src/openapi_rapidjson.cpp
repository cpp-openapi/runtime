#include "openapi_rapidjson.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

void RapidJson::SetJson(std::string data)
{
    this->_j.Parse(data.c_str());
}
    
bool RapidJson::GetInt(std::string name, int &ret)
{
    //std::cout << _j.IsObject() << _j.HasMember(name.c_str()) << _j.IsNumber() <<std::endl;
    if(!_j.IsObject() || !_j.HasMember(name.c_str())|| !_j[name.c_str()].IsInt())
    {
        ret = -1;
        return false;
    }
    ret = _j[name.c_str()].GetInt();
    return true;
}

bool RapidJson::GetString(std::string name, std::string &ret)
{
    // std::cout << _j.IsObject() << _j.HasMember(name.c_str()) << _j[name.c_str()].IsString() <<std::endl;
    if(!_j.IsObject() || !_j.HasMember(name.c_str()) || !_j[name.c_str()].IsString())
    {
        return false;
    }
    ret = std::string(_j[name.c_str()].GetString());
    return true;
}

bool RapidJson::GetObj(std::string name, std::shared_ptr<Json> &ret)
{
    if(!_j.IsObject() || !_j.HasMember(name.c_str())|| !_j[name.c_str()].IsObject())
    {
        return false;
    }
    rapidjson::Value const &v = _j[name.c_str()];
    rapidjson::Value copy(v,_j.GetAllocator());
    // todo optimize
    std::shared_ptr<RapidJson> j = std::make_shared<RapidJson>();
    j->_j.Swap(copy);
    return true;
}

bool RapidJson::ToArray(std::vector<std::shared_ptr<Json>> &ret)
{
    if (!_j.IsArray())
    {
        return false;
    }
    for (rapidjson::Value::ConstValueIterator itr = _j.Begin(); itr != _j.End(); ++itr)
    {
        rapidjson::Value const &v = *itr;
        rapidjson::Value copy(v,_j.GetAllocator());
        std::shared_ptr<RapidJson> e = std::make_shared<RapidJson>();
        e->_j.Swap(copy);
        ret.push_back(e);
    }
    return true;
}

std::string RapidJson::ToString(){
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    _j.Accept(writer);
    return std::string(buffer.GetString());
}