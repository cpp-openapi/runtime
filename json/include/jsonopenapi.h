#pragma once

// Because template with virtual member is not allowed. We implement interface with types specific functions. 

#include <string>
#include <memory>
#include <vector>

class Json
{
public:
    // sets the json content
    virtual void SetJson(std::string data) = 0;

    virtual bool HasKey(const std::string &key) = 0;
    
    virtual std::shared_ptr<Json> operator[](const std::string &key) = 0;

    virtual int GetInt() = 0;

    virtual std::string GetString() = 0;

    virtual bool GetValue(std::string name, std::shared_ptr<Json> &ret) = 0;

    virtual bool ToArray(std::vector<std::shared_ptr<Json>> &ret) = 0;

    virtual std::string ToString() = 0;

    // virtual void operator=(int val) = 0;
    // virtual void operator=(std::string val) = 0;
    virtual bool AddMemberInt(std::string name, int val) = 0;

    virtual bool AddMemberString(std::string name, std::string val) = 0;

    // obj can be array?
    virtual bool AddMember(std::string name, std::shared_ptr<Json> val) = 0;

    // is shared ptr
    template<typename T> struct is_shared_ptr : std::false_type {};
    template<typename T> struct is_shared_ptr<std::shared_ptr<T>> : std::true_type {};

    // remove shared ptr
    template<typename T>
    struct remove_shared_ptr
    {
        typedef T type;
    };

    template<typename T>
    struct remove_shared_ptr<std::shared_ptr<T>>
    {
        typedef typename remove_shared_ptr<T>::type type;
    };

    // detect vector type
    template<typename T> struct is_vector : public std::false_type {};
    template<typename T, typename A>
    struct is_vector<std::vector<T, A>> : public std::true_type {};

    // T must has deserialize function
    template<typename T>
    std::vector<T> ToArray()
    {
        std::vector<T> res;
        std::vector<std::shared_ptr<Json>> arr;
        bool isArray = this->ToArray(arr);
        // std::cout <<"is array: "<< isArray << " debug size: "<< res.size() << std::endl;
        for (auto& e : arr) {
            T i = Json::Get<T>(e);
            res.push_back(i);
            //std::cout <<"item: "<< i.id << " description: " << i.description << " string:" <<e->ToString()<<std::endl;
        }
        return res;
    }

    template<typename T>
    static T Get(std::shared_ptr<Json> j)
    {
        T i;
        // handle primitive types
        if constexpr (std::is_same<T, int>::value) 
        {
            i = j->GetInt();        
        }else if constexpr (std::is_same<T, std::string>::value)
        {
            i = j->GetString();
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
    static T GetMember(std::shared_ptr<Json> j, std::string key)
    {
        std::shared_ptr<Json> value = (*j)[key];
        if constexpr(is_vector<T>::value)
        {
            using V = typename T::value_type;
            return value->ToArray<V>();
        }else{
            return Json::Get<T>(value);
        }
    }
};