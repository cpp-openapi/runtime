#pragma once
#include "jsonopenapi.h"
#include "rapidjson/document.h"

class RapidJson : public Json
{
public:
    RapidJson() = default;
//    RapidJson(rapidjson::Document d);
    void SetJson(std::string data) override;
    
    bool GetInt(std::string name, int &ret) override;

    bool GetString(std::string name, std::string &ret) override;

    bool GetObj(std::string name, std::shared_ptr<Json> &ret) override;

    bool ToArray(std::vector<std::shared_ptr<Json>> &ret) override;

    std::string ToString() override;
private:
    void setInternal(rapidjson::Document &&j);
    rapidjson::Document _j;
};