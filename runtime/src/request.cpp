#include <request.h>

std::shared_ptr<IOASClientResponse> IOASClientRequest::GetResponse()
{
    return this->_resp;
}

ClientRequestImpl::ClientRequestImpl()
{
    this->_resp = std::make_shared<ClientResponseImpl>();
}

void IOASClientRequest::SetHeaderParam(std::string key, std::string val)
{
    this->SetHeaderParam(key, std::vector<std::string>({val}));
}

void IOASClientRequest::SetQueryParam(std::string key, std::string val)
{
    this->SetQueryParam(key, std::vector<std::string>({val}));
}

void ClientRequestImpl::SetHeaderParam(std::string key, std::vector<std::string> val)
{
    this->_header[key] = val;
}

void ClientRequestImpl::SetQueryParam(std::string key, std::vector<std::string> val)
{
    this->_query[key] = val;
}

void ClientRequestImpl::SetPathParam(std::string key, std::string val)
{
    this->_pathParam[key] = val;
}

void ClientRequestImpl::SetPathPattern(std::string path)
{
    this->_pathPattern = path;
}

void ClientRequestImpl::SetBodyParam(std::string body)
{
    this->_body = body;
}

void ClientRequestImpl::SetMethod(std::string method) 
{
    this->_method = method;    
}

// api path without basepath
std::string ClientRequestImpl::GetPath() const {
    std::string pathPattern = _pathPattern;
    // TODO: match and replace params
    for (auto const &[key, val] : this->_pathParam)
    {
        std::string const keyRep = "{" + key +"}";
        pathPattern.replace(pathPattern.find(keyRep), keyRep.size(), val.c_str());
    }
    return pathPattern;
}

std::string ClientRequestImpl::GetBody() const {
    return this->_body;
}
Header ClientRequestImpl::GetHeaderParam() const {
    return this->_header;
}
Values ClientRequestImpl::GetQueryParam() const {
    return this->_query;
}

std::string ClientRequestImpl::GetMethod() const
{
    return this->_method;
}
