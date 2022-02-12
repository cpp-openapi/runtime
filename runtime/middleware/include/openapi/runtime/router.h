#pragma once

#include <vector>
#include <set>
#include <map>
#include <utility>
#include <string>

namespace openapi{

typedef std::vector<std::pair<std::string,std::string>> PathParamValue ;

class Router
{
public:
    // returns a vector or param and its extracted values from path.
    // param is key: value in order of the appeareances in route.
    bool LookUp(const std::string & method, const std::string & path, PathParamValue &paramsRet);

    Router(std::map<std::string, std::set<std::string>> routs): routs_(routs) { }
private:
    std::map<std::string, std::set<std::string>> routs_;
};

class RouteBuilder
{
public:
    RouteBuilder& AddRoute(const std::string & method, const std::string & pathPattern);
    Router Build();
private:
    std::map<std::string, std::set<std::string>> routs_;
};

}