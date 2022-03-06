#pragma once

#include <vector>
#include <set>
#include <map>
#include <utility>
#include <string>

#include "openapi/runtime/handler.h"

namespace openapi{

std::vector<std::string> splitPath(const std::string &path);
bool isRoutPartParam(const std::string & part);

typedef std::vector<std::pair<std::string,std::string>> PathParamValue;

template <typename T>
class Router
{
public:
    // returns a vector or param and its extracted values from path.
    // param is key: value in order of the appeareances in route.
    bool LookUp(const std::string & method, const std::string & path, PathParamValue &paramsRet, T & dataRet)
    {
        PathParamValue tempParamsRet;

        // very inefficient
        if(this->routs_.count(method) == 0)
        {
            return false;
        }
        const std::map<std::string, T> &routPaths = this->routs_[method];

        std::vector<std::string> inputParts = splitPath(path);
        for(auto const& [rout, data] : routPaths)
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
                dataRet = data;
                return true;
            }
        }
        
        return false;
    }

    Router(std::map<std::string, std::map<std::string, T>> routs): routs_(routs) { }
private:
    std::map<std::string, std::map<std::string, T>> routs_;
};

template <typename T>
class RouteBuilder
{
public:
    RouteBuilder& AddRoute(const std::string & method, const std::string & pathPattern, T data)
    {
        // TODO validate method
        this->routs_[method][pathPattern] = data;
        return *this;
    }
    Router<T> Build()
    {
        return Router<T>(this->routs_);
    }
private:
    std::map<std::string, std::map<std::string, T>> routs_;
};

// generated code typically uses this:
typedef RouteBuilder<IHttpHandler> DefaultRouterBuilder;
typedef Router<IHttpHandler> DefaultRouter;

}