#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "openapi/runtime/common.h"
#include "openapi/runtime/response.h"
#include "openapi/runtime/string.h"
#include "openapi/runtime/strconv.h"
#include "openapi/runtime/type_mangle.h"


template<typename T>
T StringToType(std::string const & str){
     if constexpr (std::is_same<T, int>::value)
    {
        return std::stoi(str);
    }
    else if constexpr (std::is_same<T, std::string>::value)
    {
        return str;
    }
    else if constexpr (std::is_same<T, std::wstring>::value)
    {
        std::wstring wide = openapi::WideCharToMultiByte(str.c_str());
        return wide;
    }
    else
    {
        static_assert("Type is not supported");
        return str;
    }
}

template<typename T>
std::string TypeToString(T const & val){
    if constexpr (std::is_same<T, int>::value)
    {
        return std::to_string(val);
    }
    else if constexpr (std::is_same<T, std::string>::value)
    {
        return val;
    }
    else if constexpr (std::is_same<T, std::wstring>::value)
    {
        return openapi::MultiByteToWideChar(val.c_str());
    }
    else if constexpr (std::is_same<T, const wchar_t *>::value)
    {
        return TypeToString(std::wstring(val));
    }
    else
    {
        static_assert("Type is not supported");
        // compiler has bug that const char* is not caught
        return val;
    }
}

// data is the data in the request.
template<typename T>
std::vector<T> StrVecToTypeVec(std::vector<std::string> data)
{
    std::vector<T> retVec;
    for (std::string const & part : data)
    {
        T i = StringToType<T>(part);
        retVec.push_back(i);
    }
    return retVec;
}

template<typename T>
std::vector<std::string> TypeVecToStrVec(std::vector<T> data)
{
    std::vector<std::string> retVec;
    for (T const & part : data)
    {
        std::string i = TypeToString<T>(part);
        retVec.push_back(i);
    }
    return retVec;
}


// Request for openapi
// it can convert to http request of underlying impl
//
class IOASClientRequest
{
public:
    virtual void SetHeaderParam(std::string key, std::vector<std::string> val) = 0;
    virtual void SetQueryParam(std::string key, std::vector<std::string> val) = 0;
    virtual void SetPathParam(std::string key, std::string val) = 0;
    virtual void SetPathPattern(std::string path) = 0;
    // TODO: use stream?
    virtual void SetBodyParam(std::string body) = 0;
    virtual void SetMethod(std::string method) = 0;

    virtual std::string GetPath() const = 0;
    virtual std::string GetBody() const = 0;
    virtual Header GetHeaderParam() const = 0;
    virtual Values GetQueryParam() const = 0;
    virtual std::map<std::string, std::string> GetPathParam() const = 0;
    virtual std::string GetMethod() const = 0;

    void SetHeaderParam(std::string key, std::string val);
    void SetQueryParam(std::string key, std::string val);

    // returns response for write;
    // Typically Response and Request impl are linked, Client should not worry about which resp impl to choose.
    // Client will write to this value after request is received.
    std::shared_ptr<IOASClientResponse> GetResponse();

    template <typename T>
    void SetHeaderParam(std::string key, T val){
        if constexpr (is_vector<T>::value)
        {
            using V = typename T::value_type;
            std::vector<std::string> params = TypeVecToStrVec<V>(val);
            this->SetHeaderParam(key, openapi::JoinStrings(params, ','));
        } 
        else
        {
            this->SetHeaderParam(key, TypeToString(val));
        }

    }

    template <typename T>
    void SetQueryParam(std::string key, T val){
        if constexpr (is_vector<T>::value)
        {
            using V = typename T::value_type;
            std::vector<std::string> params = TypeVecToStrVec<V>(val);
            this->SetQueryParam(key, openapi::JoinStrings(params, ','));
        }
        else 
        {
            this->SetQueryParam(key, TypeToString(val));
        }
    }

    template <typename T>
    void SetPathParam(std::string key, T val){
        // path cannot take vector values
        this->SetPathParam(key, TypeToString(val));
    }

    template <typename T>
    bool GetHeaderParam(std::string key, T & ret)
    {
        Header const & vals = this->GetHeaderParam();
        if (vals.find(key) == vals.end())
        {
            return false;
        }

        std::vector<std::string> const & val = vals.at(key);
        if(val.size() == 0)
        {
            return false;
        }

        if constexpr (is_vector<T>::value)
        {
            using V = typename T::value_type;
            ret = StrVecToTypeVec<V>(val);
            return true;
        }
        else
        {
            ret = StringToType<T>(val[0]);
            return true;
        }
    }

    template <typename T>
    bool GetQueryParam(std::string key, T & ret)
    {
        Values const & vals = this->GetQueryParam();
        if (vals.find(key) == vals.end())
        {
            return false;
        }

        std::vector<std::string> const & val = vals.at(key);
        if(val.size() == 0)
        {
            return false;
        }

        if constexpr (is_vector<T>::value)
        {
            using V = typename T::value_type;
            ret = StrVecToTypeVec<V>(val);
            return true;
        }
        else
        {
            // take the first one otherwise
            ret = StringToType<T>(val[0]);
            return true;
        }
    }

    template <typename T>
    bool GetPathParam(std::string key, T & ret)
    {
        std::map<std::string, std::string> const & vals = this->GetPathParam();
        if (vals.find(key) == vals.end())
        {
            return false;
        }
        ret = StringToType<T>(vals.at(key));
        return true;
    }

protected:
    // resp that is used to write.
    std::shared_ptr<IOASClientResponse> _resp;
};

class ClientRequestImpl : public IOASClientRequest
{
    std::string _method;
    std::string _pathPattern; // path for the api after base path
    Header _header;
    Values _query;
    std::string _body;
    std::map<std::string, std::string> _pathParam;

public:
    ClientRequestImpl();
    void SetHeaderParam(std::string key, std::vector<std::string> val) override;
    void SetQueryParam(std::string key, std::vector<std::string> val) override;
    void SetPathParam(std::string key, std::string val) override;
    void SetPathPattern(std::string path) override;
    // TODO: use stream?
    void SetBodyParam(std::string body) override;
    void SetMethod(std::string method) override;

    std::string GetPath() const override;
    std::string GetBody() const override;
    Header GetHeaderParam() const override;
    Values GetQueryParam() const override;
    std::map<std::string, std::string> GetPathParam() const override;
    std::string GetMethod() const override;
};

// generated param needs to implement this
// class IClientRequestWriter
// {
// public:
//     virtual void WriteToClientRequest(std::shared_ptr<IOASClientRequest> req);
// };