#pragma once

#include "jsonopenapi.h"
#include <nlohmann/json.hpp>
#include <memory>

class NlohmannJson : public Json
{
public:
    std::shared_ptr<Json> New() override;

    void SetJson(std::string data) override;

    bool HasKey(const std::string &key);
    
    std::shared_ptr<Json> operator[](const std::string &key) override;

    int GetInt() override;

    void SetInt(int val) override;

    std::string GetString() override;

    void SetString(std::string val) override;

    bool GetValue(std::string name, std::shared_ptr<Json> &ret) override;

    bool ToArray(std::vector<std::shared_ptr<Json>> &ret) override;

    void FlattenFrom(std::vector<std::shared_ptr<Json>> arr) override;

    std::string ToString() override;

    bool AddMemberInt(std::string name, int val) override;

    bool AddMemberString(std::string name, std::string val) override;

    // obj can be array?
    bool AddMember(std::string name, std::shared_ptr<Json> val) override;

    // std::shared_ptr<Json> NewMember(std::string name);

    // //void operator=(std::shared_ptr<Json> val);
    // void operator=(int val) override;
    // void operator=(std::string val) override;
    
private:
    void setInternal(nlohmann::json j);
    nlohmann::json _j;
};