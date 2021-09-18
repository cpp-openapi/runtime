#include "openapi_nlohmann_json.h"
// #include <iostream>
#include <exception>

std::shared_ptr<Json>  NlohmannJson::operator[](const std::string &key)
{
    std::shared_ptr<NlohmannJson> j = std::make_shared<NlohmannJson>();

    if (!this->HasKey(key))
    {
        throw new std::invalid_argument("key not found");
    }

    j->_j = this->_j.at(key);
    return j;
}

bool NlohmannJson::HasKey(const std::string &key)
{
    return this->_j.contains(key);
}

int NlohmannJson::GetInt()
{
    if(!this->_j.is_number_integer()){
        throw new std::invalid_argument("not integer");
    }
    int ret = 0;
    this->_j.get_to<int>(ret);
    return ret;
}

std::string NlohmannJson::GetString()
{
    if(!this->_j.is_string()){
        throw new std::invalid_argument("not string");
    }
    std::string ret;
    this->_j.get_to<std::string>(ret);
    return ret;
}

void NlohmannJson::SetJson(std::string data)
{
    
    this->_j = nlohmann::json::parse(data);
}

bool NlohmannJson::GetObj(std::string name, std::shared_ptr<Json> &ret)
{
    if (!this->_j.contains(name))
    {   
        return false;
    }
    // TODO: this is no efficient?
    nlohmann::json inner = this->_j.at(name);
    std::shared_ptr<NlohmannJson> np = std::make_shared<NlohmannJson>();
    np->setInternal(inner);
    ret = np;
    return true;
}

void NlohmannJson::setInternal(nlohmann::json j)
{
    this->_j = j;
}

bool NlohmannJson::ToArray(std::vector<std::shared_ptr<Json>> &ret) 
{
    if (!this->_j.is_array())
    {
        return false;
    }
   // nlohmann::json arr =  nlohmann::json::array(_j);

    std::vector<std::shared_ptr<Json>> res;
    for (nlohmann::json::iterator it = _j.begin(); it != _j.end(); ++it)
    {
        nlohmann::json item = *it;
        // std::cout << "json debug to array: " << item << std::endl;
        std::shared_ptr<NlohmannJson> jItem = std::make_shared<NlohmannJson>();
        jItem->setInternal(item);
        res.push_back(jItem);
    }
    ret = res;
    return true;
}

std::string NlohmannJson::ToString(){
    return this->_j.dump();
}

bool NlohmannJson::AddMemberInt(std::string name, int val)
{
    this->_j[name] = val;
    return true;
}

bool NlohmannJson::AddMemberString(std::string name, std::string val)
{
    this->_j[name] = val;
    return true;
}

// obj can be array?
bool NlohmannJson::AddMember(std::string name, std::shared_ptr<Json> val)
{
    std::shared_ptr<NlohmannJson> j = std::dynamic_pointer_cast<NlohmannJson>(val);
    this->_j[name] = j->_j;
    return true;
}

// void NlohmannJson::operator=(int val)
// {
//     _j = val;
// }

// void NlohmannJson::operator=(std::string val)
// {
//     _j = val;
// }

//  std::shared_ptr<Json> NlohmannJson::NewMember(std::string name)
//  {
//      std::shared_ptr<NlohmannJson> nm = std::make_shared<NlohmannJson>();

//      nm->_j = _j[name];
//  }