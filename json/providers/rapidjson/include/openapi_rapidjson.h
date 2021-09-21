#pragma once
#include "jsonopenapi.h"
#include "rapidjson/document.h"

class RapidJson : public Json
{
public:
    RapidJson() = default;
//    RapidJson(rapidjson::Document d);
    void SetJson(std::string data) override;

    bool HasKey(const std::string &key) override;
    
    std::shared_ptr<Json> operator[](const std::string &key) override;

    int GetInt() override;

    std::string GetString() override;

    bool GetValue(std::string name, std::shared_ptr<Json> &ret) override;

    bool ToArray(std::vector<std::shared_ptr<Json>> &ret) override;

    std::string ToString() override;

    bool AddMemberInt(std::string name, int val) override;

    bool AddMemberString(std::string name, std::string val) override;

    bool AddMember(std::string name, std::shared_ptr<Json> val) override;
    // void operator=(int val) override;
    // void operator=(std::string val) override;
private:
    void setInternal(rapidjson::Document &&j);
    rapidjson::Document _j;
};