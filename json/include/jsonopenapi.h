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

    virtual bool GetObj(std::string name, std::shared_ptr<Json> &ret) = 0;

    virtual bool ToArray(std::vector<std::shared_ptr<Json>> &ret) = 0;

    virtual std::string ToString() = 0;

    // virtual void operator=(int val) = 0;
    // virtual void operator=(std::string val) = 0;
    virtual bool AddMemberInt(std::string name, int val) = 0;

    virtual bool AddMemberString(std::string name, std::string val) = 0;

    // obj can be array?
    virtual bool AddMember(std::string name, std::shared_ptr<Json> val) = 0;

    // T must has deserialize function
    template<typename T>
    std::vector<T> ToArray()
    {
        std::vector<T> res;
        std::vector<std::shared_ptr<Json>> arr;
        bool isArray = this->ToArray(arr);
        // std::cout <<"is array: "<< isArray << " debug size: "<< res.size() << std::endl;
        for (auto& e : arr) {
            T i;
            i.json_deserialize(e);
            res.push_back(i);
            //std::cout <<"item: "<< i.id << " description: " << i.description << " string:" <<e->ToString()<<std::endl;
        }
        return res;
    }
};