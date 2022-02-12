#include "openapi/runtime/router.h"

using namespace openapi;

RouteBuilder& RouteBuilder::AddRoute(const std::string & method, const std::string & pathPattern)
{
    // TODO validate method
    this->routs_[method].emplace(pathPattern);
    return *this;
}

Router RouteBuilder::Build()
{
    return Router(this->routs_);
}

std::vector<std::string> splitPath(const std::string &path)
{
    std::vector<std::string> res;
    static const std::string delimiter = "/";
    auto start = 0U;
    auto end = path.find(delimiter);
    while (end != std::string::npos)
    {
        std::string part = path.substr(start, end - start);
        res.push_back(part);
        start = end + delimiter.length();
        end = path.find(delimiter, start);
    }
    std::string part = path.substr(start, end);
    res.push_back(part);
    return res;
}

bool isRoutPartParam(const std::string & part)
{
    if(part.size() == 0)
    {
        return false;
    }
    return (part.at(0) == '{' && part.at(part.size()-1) == '}');
}

bool Router::LookUp(const std::string & method, const std::string & path, PathParamValue &paramsRet)
{
    PathParamValue tempParamsRet;

    // very inefficient
    if(this->routs_.count(method) == 0)
    {
        return false;
    }
    const std::set<std::string> &routPaths = this->routs_[method];

    std::vector<std::string> inputParts = splitPath(path);
    for(const std::string &rout : routPaths)
    {
        std::vector<std::string> routParts = splitPath(rout);
        if(routParts.size() != inputParts.size())
        {
            continue;
        }

        bool routMatched = true;
        for(std::size_t i = 0; i < routParts.size(); i++)
        {
            std::string & routPart = routParts[i];
            std::string & inputPart = inputParts[i];
            if(isRoutPartParam(routPart))
            {
                std::string routPartKey = std::string(routPart.begin()+ 1, routPart.end() - 1);
                tempParamsRet.push_back(std::make_pair(routPartKey, inputPart));
            }
            else
            {
                if(routPart != inputPart)
                {
                    // this route doees not match
                    tempParamsRet.clear();
                    routMatched = false;
                    break;
                }
            }
        }
        if(routMatched)
        {
            if(tempParamsRet.size() > 0)
            {
                paramsRet.insert(paramsRet.end(), tempParamsRet.begin(), tempParamsRet.end());
            }
            return true;
        }
    }
    
    return false;
}