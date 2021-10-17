#include "openapi_rapidjson.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

std::shared_ptr<Json> RapidJson::New()
{
    return std::make_shared<RapidJson>();
}

std::shared_ptr<Json>  RapidJson::GetMember(const std::string &key)
{
    if (!this->HasKey(key))
    {
        throw new std::invalid_argument("key not found");
    }

    rapidjson::Value const &v = _j[key.c_str()];
    rapidjson::Value copy;
    copy.CopyFrom(v,_j.GetAllocator());
    // todo optimize
    std::shared_ptr<RapidJson> j = std::make_shared<RapidJson>();
    j->_j.CopyFrom(copy.Move(),j->_j.GetAllocator());
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

void RapidJson::SetInt(int val)
{
    this->_j.SetInt(val);
}

std::string RapidJson::GetString()
{
    if(!this->_j.IsString()){
        throw new std::invalid_argument("not string");
    }
    std::string ret = _j.GetString();
    return ret;
}

void RapidJson::SetString(std::string val)
{
    this->_j.SetString(val.c_str(),val.size(),_j.GetAllocator());
}

void RapidJson::Parse(std::string data)
{
    this->_j.Parse(data.c_str());
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
        // rapidjson::Value copy(v,_j.GetAllocator());
        std::shared_ptr<RapidJson> e = std::make_shared<RapidJson>();
        rapidjson::Value copy(v, this->_j.GetAllocator());
        e->_j.Swap(copy);
        ret.push_back(e);
    }
    return true;
}

// TODO: implement this
void RapidJson::FlattenFrom(std::vector<std::shared_ptr<Json>> arr)
{
    this->_j.SetArray();
    for (const std::shared_ptr<Json> & j : arr)
    {
        std::shared_ptr<RapidJson> jj = std::dynamic_pointer_cast<RapidJson>(j);
        rapidjson::Value copy(jj->_j, this->_j.GetAllocator());
        this->_j.PushBack(copy,this->_j.GetAllocator());
    }
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
    _j.AddMember(key.Move(), val, _j.GetAllocator());
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
    _j.AddMember(key.Move(), v.Move(), _j.GetAllocator());
    return true;
}

bool RapidJson::AddMember(std::string name, std::shared_ptr<Json> val)
{
    rapidjson::Value key;
    key.SetString(name.c_str(),name.size(),_j.GetAllocator());

    std::shared_ptr<RapidJson> j = std::dynamic_pointer_cast<RapidJson>(val);
    rapidjson::Value copy(j->_j, _j.GetAllocator());
    _j.AddMember(key.Move(), copy.Move(), _j.GetAllocator());
    return true;
}