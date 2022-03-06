#include "openapi/runtime/router.h"

using namespace openapi;

std::vector<std::string> openapi::splitPath(const std::string &path)
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

bool openapi::isRoutPartParam(const std::string & part)
{
    if(part.size() == 0)
    {
        return false;
    }
    return (part.at(0) == '{' && part.at(part.size()-1) == '}');
}