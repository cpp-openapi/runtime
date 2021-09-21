#include "openapi_rapidjson.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

std::shared_ptr<Json>  RapidJson::operator[](const std::string &key)
{
    if (!this->HasKey(key))
    {
        throw new std::invalid_argument("key not found");
    }

    rapidjson::Value const &v = _j[key.c_str()];
    rapidjson::Value copy(v,_j.GetAllocator());
    // todo optimize
    std::shared_ptr<RapidJson> j = std::make_shared<RapidJson>();
    j->_j.Swap(copy);
    return j;
}

bool RapidJson::HasKey(const std::string &key)
{
    return this->_j.HasMember(key.c_str());
}

int RapidJson::GetInt()
{
    if(!this->_j.IsInt()){
        throw new std::invalid_argument("not integer");
    }
    int ret = _j.GetInt();
    return ret;
}

std::string RapidJson::GetString()
{
    if(!this->_j.IsString()){
        throw new std::invalid_argument("not string");
    }
    std::string ret = _j.GetString();
    return ret;
}

void RapidJson::SetJson(std::string data)
{
    this->_j.Parse(data.c_str());
}

bool RapidJson::GetValue(std::string name, std::shared_ptr<Json> &ret)
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

// void RapidJson::operator=(int val)
// {
//     _j.SetInt(val);
// }

// void RapidJson::operator=(std::string const val)
// {
//     _j.SetString(val.c_str(),_j.GetAllocator());
// }

bool RapidJson::AddMemberInt(std::string name, int val)
{
    if(_j.IsNull()){
        _j.SetObject();
    } // todo error
    //kvs.SetObject();
    rapidjson::Value key;
    key.SetString(name.c_str(),name.size(),_j.GetAllocator());
    _j.AddMember(key, val, _j.GetAllocator());
    return true;
}

bool RapidJson::AddMemberString(std::string name, std::string val)
{
    if(_j.IsNull()){
        _j.SetObject();
    }
    //_j.SetObject();
    rapidjson::Value key;
    key.SetString(name.c_str(),name.size(),_j.GetAllocator());
    rapidjson::Value v;
    v.SetString(val.c_str(),val.size(),_j.GetAllocator());
    _j.AddMember(key, v, _j.GetAllocator());
    return true;
}

bool RapidJson::AddMember(std::string name, std::shared_ptr<Json> val)
{
    // TODO fix this
    rapidjson::Value kvs;
    rapidjson::Value key;
    key.SetString(name.c_str(),name.size(),_j.GetAllocator());

    std::shared_ptr<RapidJson> j = std::dynamic_pointer_cast<RapidJson>(val);
    
    if(j->_j.IsObject() || j->_j.IsArray()){
        kvs.AddMember(key, j->_j, _j.GetAllocator());
    }

    return true;
    //kvs.AddMember(key, val, _j.GetAllocator());
}