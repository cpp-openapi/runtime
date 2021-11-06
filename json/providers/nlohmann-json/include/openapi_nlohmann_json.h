#pragma once

// #include "jsonopenapi.h"
#include "runtime_types.h"
#include <nlohmann/json.hpp>
#include <memory>

class NlohmannJson
{
public:
    NlohmannJson(): _j() { }

    void Parse(const std::string &data);

    bool HasKey(const std::string &key) const;


    std::string ToString() const;

    template<typename T>
    static NlohmannJson Serialize(T val);

    template<typename T>
    T Get() const;
    
    template<typename T>
    T GetMember(const std::string &key) const;

    template<typename T>
    void AddMember(const std::string &key, T val);

    // set json value, used mainly for array
    template<typename T>
    void Set(T val);

private:
    NlohmannJson(nlohmann::json j): _j(j) { }
    nlohmann::json _j;
};

template<typename T>
NlohmannJson NlohmannJson::Serialize(T val)
{
    NlohmannJson j;
    j.Set(val);
    return j;
}

// T is primitive or vector or deserializable
template<typename T>
T NlohmannJson::Get() const
{
    T i;
    if constexpr (is_optional<T>::value)
    {
        // For optional, get the inner type
        using V = typename remove_optional<T>::type;
        i = this->Get<V>();
    }
    // handle primitive types
    else if constexpr (std::is_same<T, int>::value || std::is_same<T, std::string>::value) 
    {
        this->_j.get_to<T>(i);       
    }
    else if constexpr(is_vector<T>::value)
    {
        using V = typename T::value_type;
        if(!this->_j.is_array())
        {
            throw new std::runtime_error("json is not array");
        }
        // traverse array
        for (nlohmann::json::const_iterator it = this->_j.begin(); it != this->_j.end(); ++it)
        {
            NlohmannJson item(*it);
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
T NlohmannJson::GetMember(const std::string &key) const
{
    if (!this->HasKey(key))
    {
        throw new std::invalid_argument("key not found");
    }

    nlohmann::json inner = this->_j.at(key);
    NlohmannJson j2;
    j2._j = inner;
    return j2.Get<T>();
}

template<typename T>
void NlohmannJson::Set(T val)
{
    if constexpr(is_optional<T>::value)
    {
        if(val.has_value()){
            using V = typename remove_optional<T>::type;
            this->Set<V>(val.value());
        }
        // TODO: set null?
    }
    else if constexpr (std::is_same<T, int>::value 
        || std::is_same<T, std::string>::value) 
    {
        this->_j = val;     
    }
    else if constexpr(std::is_same<T, NlohmannJson>::value)
    {
        this->_j = val._j;
    }
    else if constexpr(is_vector<T>::value)
    {
        for(auto & e : val)
        {
            NlohmannJson item;
            item.Set(e);
            this->_j.push_back(item._j);
        }
    }
    else
    {
        // TODO:
        if constexpr (is_shared_ptr<T>::value == true)
        {
            this->_j = val->SerializeJSON()._j;
        }
        else
        {
            this->_j = val.SerializeJSON()._j;
        }
    }
}


template<typename T>
void NlohmannJson::AddMember(const std::string &key, T val)
{
    NlohmannJson jVal;
    jVal.Set(val);
    this->_j[key] = jVal._j;
}