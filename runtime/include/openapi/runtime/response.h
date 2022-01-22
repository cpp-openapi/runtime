#pragma once

#include "openapi/runtime/common.h"
#include <sstream>

class IOASClientResponse
{
public:
    virtual void SetHeaderResp(std::string key, std::vector<std::string> val) = 0;
    // TODO: use stream?
    virtual void SetBodyResp(std::string body) = 0;
    virtual void SetCode(int code) = 0;

    virtual std::string GetBody() const = 0;
    virtual std::string GetHeader(std::string key) const = 0;
    virtual int GetCode() const = 0;
    virtual std::ostream& GetBodyOStream() = 0;
    virtual std::istream& GetBodyIStream() = 0;
};

class ClientResponseImpl : public IOASClientResponse
{
    Header _header;
    Values _query;
    int _code;
    std::stringstream _bodyStream;
public:
    void SetHeaderResp(std::string key, std::vector<std::string> val) override;
    void SetBodyResp(std::string body) override;
    void SetCode(int code) override;

    std::string GetBody() const override;
    std::string GetHeader(std::string key) const override;
    int GetCode() const override;
    std::ostream& GetBodyOStream() override;
    std::istream& GetBodyIStream() override;
};

class EmptyPayload{};
