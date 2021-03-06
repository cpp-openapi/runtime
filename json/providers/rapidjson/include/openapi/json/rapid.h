#pragma once

#include "openapi/runtime/string.h"
#include "openapi/runtime/type_mangle.h"
#include "openapi/runtime/strconv.h"
#include "rapidjson/document.h"
#include <memory>
#include <string>
#include <stdexcept>

class RapidJson
{
public:
    RapidJson(): _j() { }

    void Parse(const openapi::string_t & data);

    bool HasKey(const openapi::string_t &key) const;

    openapi::string_t ToString() const;

    template<typename T>
    static openapi::string_t Serialize(T val);

    template<typename T>
    static T Deserialize(const openapi::string_t &data);

    template<typename T>
    T Get() const;
    
    template<typename T>
    T GetMember(const openapi::string_t &key) const; // cannot make const?

    template<typename T>
    void AddMember(const openapi::string_t &key, T val);

    // set json value, used mainly for array
    template<typename T>
    void Set(T val);

private:
    rapidjson::Document _j;
};

template<typename T>
openapi::string_t RapidJson::Serialize(T val)
{
    RapidJson j;
    j.Set(val);
    return j.ToString();
}

template<typename T>
T RapidJson::Deserialize(const openapi::string_t &data)
{
    RapidJson j;
    j.Parse(data);
    return j.Get<T>();
}

template<typename T>
T RapidJson::Get() const
{
    T i;
    if constexpr (is_optional<T>::value)
    {
        // For optional, get the inner type
        using V = typename remove_optional<T>::type;
        i = this->Get<V>();
    }
    // handle primitive types
    else if constexpr (std::is_same<T, int>::value) 
    {
        if(!this->_j.IsInt()){
            throw new std::invalid_argument("not integer");
        }
        i = this->_j.GetInt();     
    }
    else if constexpr (std::is_same<T, bool>::value) 
    {
        if(!this->_j.IsBool())
        {
            throw new std::invalid_argument("not bool");
        }
        i = this->_j.GetBool();
    }
    else if constexpr (std::is_same<T, openapi::string_t>::value)
    {
        if(!this->_j.IsString()){
            throw new std::invalid_argument("not string");
        }
        std::string stdVal = _j.GetString();
        i = openapi::StringT(stdVal.c_str());
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
            RapidJson item;
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
            i->FromJSON(*this);
        }else{
            i.FromJSON(*this);
        }
    }
    return i;
}

template<typename T>
T RapidJson::GetMember(const openapi::string_t &key) const
{
    if (!this->HasKey(key))
    {
        throw new std::invalid_argument("key not found");
    }

    rapidjson::Value const &v = _j[openapi::ToStdString(key).c_str()];
    RapidJson inner;
    inner._j.CopyFrom(v, inner._j.GetAllocator());
    return inner.Get<T>();
}

template<typename T>
void RapidJson::Set(T val)
{
    if constexpr(is_optional<T>::value)
    {
        if(val.has_value()){
            using V = typename remove_optional<T>::type;
            this->Set<V>(val.value());
        }
        // TODO: set null?
    }
    else if constexpr (std::is_same<T, int>::value) 
    {
        this->_j.SetInt(val);
    }
    else if constexpr (std::is_same<T, bool>::value) 
    {
        this->_j.SetBool(val);
    }
    else if constexpr (std::is_same<T, openapi::string_t>::value)
    {
        std::string stdVal = openapi::ToStdString(val);
        this->_j.SetString(stdVal.c_str(),static_cast<rapidjson::SizeType>(stdVal.size()),_j.GetAllocator());
    }
    else if constexpr(std::is_same<T, RapidJson>::value)
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
            RapidJson item;
            item.Set(e);
            rapidjson::Value copy(item._j, this->_j.GetAllocator());
            this->_j.PushBack(copy.Move(), this->_j.GetAllocator());
        }
    }
    else
    {
        if constexpr (is_shared_ptr<T>::value == true)
        {
            RapidJson i;
            val->ToJSON(i);
            this->_j.CopyFrom(i._j, this->_j.GetAllocator());
        }
        else
        {
            RapidJson i;
            val.ToJSON(i);
            this->_j.CopyFrom(i._j, this->_j.GetAllocator());
        }
    }
}

template<typename T>
void RapidJson::AddMember(const openapi::string_t &key, T val)
{
    rapidjson::Value name;
    std::string stdKey = openapi::ToStdString(key);
    name.SetString(stdKey.c_str(),static_cast<rapidjson::SizeType>(stdKey.size()),_j.GetAllocator());
    
    RapidJson jVal;
    jVal.Set<T>(val);
    rapidjson::Value copy(jVal._j, this->_j.GetAllocator());

    // if type is not initilized, member will not be added
    if(_j.IsNull()){
        _j.SetObject();
    }
    this->_j.AddMember(name.Move(), copy.Move(), _j.GetAllocator());
}