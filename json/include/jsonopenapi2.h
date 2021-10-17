#pragma once

// Because template with virtual member is not allowed. We implement interface with types specific functions. 

#include <string>
#include <memory>
#include <vector>
#include "runtime_types.h"

// inner json. Must implemente Json1 virtual functions
template<typename J>
class Json2
{
public:
    Json2(): inner_() { }

    Json2(J inner): inner_(inner) { }

    J inner_;

    // T must has deserialize function
    template<typename T>
    std::vector<T> ToArray()
    {
        std::vector<T> res;
        std::vector<std::shared_ptr<Json>> arr;
        bool isArray = inner_.ToArray(arr);
        // std::cout <<"is array: "<< isArray << " debug size: "<< res.size() << std::endl;
        for (auto& e : arr) {
            T i = Json2::Get<T>(e);
            res.push_back(i);
            //std::cout <<"item: "<< i.id << " description: " << i.description << " string:" <<e->ToString()<<std::endl;
        }
        return res;
    }

    template<typename T>
    static T Get(std::shared_ptr<Json2> j)
    {
        T i;
        // handle primitive types
        if constexpr (std::is_same<T, int>::value) 
        {
            i = j->inner_.GetInt();        
        }else if constexpr (std::is_same<T, std::string>::value)
        {
            i = j->inner_.GetString();
        }
        else if constexpr(is_vector<T>::value)
        {
            using V = typename T::value_type;
            i = j->ToArray<V>(); // json2 to array
        }
        else
        {
            // TODO: use declare type in c++17 or requires in c++20
            if constexpr (is_shared_ptr<T>::value == true)
            {
                using U = typename remove_shared_ptr<T>::type;
                i = std::make_shared<U>();
                i->DeserializeJSON(j);
            }else{
                i.DeserializeJSON(j);
            }
        }
        return i;
    }

    template<typename T>
    static T GetMember(std::shared_ptr<Json2> j, std::string key)
    {
        std::shared_ptr<Json2> value = j->inner_.GetMember(key);
        return Json2::Get<T>(value);
    }

    // copy val into j
    template<typename T>
    static void ToJson(std::shared_ptr<Json2> j, T val){
        if constexpr (std::is_same<T, int>::value)
        {
            j->SetInt(val);
        }
        else if constexpr (std::is_same<T, std::string>::value)
        {
            j->SetString(val);
        }
        else if constexpr (is_vector<T>::value)
        {
            Json::ToJsonArray(j, val);
        }
        else
        {
            // structs
            if constexpr (is_shared_ptr<T>::value == true)
            {
                val->SerializeJSON(j);
            }
            else
            {
                val.SerializeJSON(j);
            }
        }
    }

    // copy arr in to j
    template<typename T>
    static void ToJsonArray(std::shared_ptr<Json> j, std::vector<T> arr)
    {
        std::vector<std::shared_ptr<Json>> ret;
        // TODO set int etc
        for(const T e : arr)
        {
            std::shared_ptr<Json> je = j->New();
            Json::ToJson(je, e);
            ret.push_back(je);
        }
        j->FlattenFrom(ret);
    }

    template<typename T>
    static void AddMember(std::shared_ptr<Json> j, std::string key, T val)
    {
        if constexpr (std::is_same<T, int>::value)
        {
            j->AddMemberInt(key,val);
        }
        else if constexpr (std::is_same<T, std::string>::value)
        {
            j->AddMemberString(key,val);
        }
        else if constexpr (is_vector<T>::value)
        {
            std::shared_ptr<Json> jVal = j->New();
            Json::ToJson(jVal, val);
            j->AddMember(key, jVal);
        }
        else
        {
            std::shared_ptr<Json> jVal = j->New();
            if constexpr (is_shared_ptr<T>::value == true)
            {
                val->SerializeJSON(jVal);
            }
            else
            {
                val.SerializeJSON(jVal);
            }
            j->AddMember(key, jVal);
        }
    }
};