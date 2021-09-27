#include "curlppclient.h"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>
#include <sstream>

curlpp::OptionBase *makeMethodOpt(std::string method)
{
    if (method == "GET")
    {
        return new curlpp::options::HttpGet(true);
    }
    if (method == "POST")
    {
        return new curlpp::options::Post(true);
    }
    if (method == "PUT")
    {
        return new curlpp::options::Put(true);
    }
    if (method == "DELETE")
    {
        return new curlpp::options::CustomRequest{"DELETE"};
    }
    throw std::invalid_argument("Method: " + method + " is not recognized");
}

void CurlPPClient::MakeRequest(const IOASClientRequest &req, IOASClientResponse &resp)
{

    std::string url = "http://" + this->_cfg.Host + ":" + this->_cfg.Port + this->_cfg.BasePath;
    if (req.GetPath().size() != 0)
    {
        // remove last slash of base path
        if(url[url.size()-1] == '/')
        {
            url = url.substr(0, url.size()-1);
        }
        // path always has leading slash
        url += req.GetPath();
    }

    curlpp::Cleanup cleaner;
    curlpp::Easy request;

    std::list<std::string> headers;
    const Header &h = req.GetHeaderParam();
    for (auto const &[key, val] : h)
    {
        // use the first val. TODO: fix this
        if (val.size() == 0)
        {
            continue;
        }
        headers.push_back(key + ": " + val[0]);
    }
    //std::cout << "debug header:" << headers << std::endl;

    using namespace curlpp::Options;
    request.setOpt(new HttpHeader(headers));
    // sprintf(buf, "Content-Length: %d", size);
    //headers.push_back(buf);

    // needs to be built manually
    const Values &q = req.GetQueryParam();
    if (q.size() != 0){
        url += "?";
        for (auto const &[key, val] : q)
        {
            // use the first val. TODO: fix this
            if (val.size() == 0)
            {
                continue;
            }
            url += (key + "=" + val[0]);
        }
    }

    request.setOpt(makeMethodOpt(req.GetMethod()));

    if (this->_debug)
    {
        request.setOpt(new Verbose(true));
    }

    const std::string &body = req.GetBody();
    if (body.size() != 0)
    {
        request.setOpt(new curlpp::options::PostFields(req.GetBody()));
        request.setOpt(new curlpp::options::PostFieldSize(req.GetBody().length()));
    }
    request.setOpt(new Url(url));

    std::stringstream os;
    curlpp::options::WriteStream ws(&os);
    request.setOpt(ws);
    request.perform();

    resp.SetBodyResp(os.str());
    long http_code = curlpp::infos::ResponseCode::get(request);
    resp.SetCode(http_code);
    // TODO set header
}

void CurlPPClient::SetDebug(bool debug)
{
    this->_debug = debug;
}