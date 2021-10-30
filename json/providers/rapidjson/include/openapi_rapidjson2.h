#pragma once

#include "runtime_types.h"
#include "rapidjson/document.h"
#include <memory>
#include <string>

class RapidJson2
{
public:
    RapidJson2(): _j() { }

    void Parse(const std::string & data);

    bool HasKey(const std::string &key) const;

    std::string ToString();

    template<typename T>
    T Get() const;
    
    template<typename T>
    T GetMember(const std::string &key) const; // cannot make const?

    template<typename T>
    void AddMember(const std::string &key, T val);

    // set json value, used mainly for array
    template<typename T>
    void Set(T val);

private:
    rapidjson::Document _j;
};

template<typename T>
T RapidJson2::Get() const
{
    T i;
    // handle primitive types
    if constexpr (std::is_same<T, int>::value) 
    {
        if(!this->_j.IsInt()){
            throw new std::invalid_argument("not integer");
        }
        i = this->_j.GetInt();     
    }
    else if constexpr (std::is_same<T, std::string>::value)
    {
        if(!this->_j.IsString()){
            throw new std::invalid_argument("not string");
        }
        i = _j.GetString();
    }
    else if constexpr(is_vector<T>::value)
    {
        using V = typename T::value_type;
        if(!this->_j.IsArray())
        {
            throw new std::runtime_error("json is not array");
        }
        // traverse array
        for (rapidjson::Value::ConstValueIterator it = this->_j.Begin(); it != this->_j.End(); ++it)
        {
            RapidJson2 item;
            rapidjson::Value const &v = *it;
            item._j.CopyFrom(v, item._j.GetAllocator());
            i.push_back(item.Get<V>());
        }
    }
    else
    {
        // TODO: use declare type in c++17 or requires in c++20
        if constexpr (is_shared_ptr<T>::value == true)
        {
            using U = typename remove_shared_ptr<T>::type;
            i = std::make_shared<U>();
            i->DeserializeJSON(*this);
        }else{
            i.DeserializeJSON(*this);
        }
    }
    return i;
}

template<typename T>
T RapidJson2::GetMember(const std::string &key) const
{
    if (!this->HasKey(key))
    {
        throw new std::invalid_argument("key not found");
    }

    rapidjson::Value const &v = _j[key.c_str()];
    RapidJson2 inner;
    inner._j.CopyFrom(v, inner._j.GetAllocator());
    return inner.Get<T>();
}

template<typename T>
void RapidJson2::Set(T val)
{
    if constexpr (std::is_same<T, int>::value) 
    {
        this->_j.SetInt(val);
    }
    else if constexpr (std::is_same<T, std::string>::value)
    {
        this->_j.SetString(val.c_str(),static_cast<rapidjson::SizeType>(val.size()),_j.GetAllocator());
    }
    else if constexpr(std::is_same<T, RapidJson2>::value)
    {
        // TODO??
        this->_j = val._j;
    }
    else if constexpr(is_vector<T>::value)
    {
        if (this->_j.IsNull())
        {
            this->_j.SetArray();
        }
        for(auto & e : val)
        {
            RapidJson2 item;
            item.Set(e);
            rapidjson::Value copy(item._j, this->_j.GetAllocator());
            this->_j.PushBack(copy.Move(), this->_j.GetAllocator());
        }
    }
    else
    {
        if constexpr (is_shared_ptr<T>::value == true)
        {
            this->_j.CopyFrom(val->SerializeJSON()._j, this->_j.GetAllocator());
        }
        else
        {
            this->_j.CopyFrom(val.SerializeJSON()._j, this->_j.GetAllocator());
        }
    }
}

template<typename T>
void RapidJson2::AddMember(const std::string &key, T val)
{
    rapidjson::Value name;
    name.SetString(key.c_str(),static_cast<rapidjson::SizeType>(key.size()),_j.GetAllocator());
    
    RapidJson2 jVal;
    jVal.Set(val);
    rapidjson::Value copy(jVal._j, this->_j.GetAllocator());

    // if type is not initilized, member will not be added
    if(_j.IsNull()){
        _j.SetObject();
    }
    this->_j.AddMember(name.Move(), copy.Move(), _j.GetAllocator());
}