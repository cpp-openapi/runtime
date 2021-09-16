# cpp-openapi runtime
(In development)

An abstraction layer for various http libs for C++.

Once this layer is stabilized, an openapi-generator can generate client code on top of this layer.

## Open questions
* Async logic for different libs
## TODO
* scheme https. need SSL lib dependency. For now only http is supported.

## Snippet
```cpp
    ClientConfig cfg = {
        "localhost",
        "12345",
        "/",
        };
    // use curl backend
    std::shared_ptr<IClient> cli =  std::make_shared<CurlPPClient>(cfg);

    // use boost::beast backend
    // std::shared_ptr<IClient> cli =  std::make_shared<BeastClient>(cfg);

    // Set headers etc
    ClientRequestImpl cri;
    cri.SetHeaderParam("api-token",{"my-token"});
    cri.SetMethod("GET");

    ClientResponseImpl respRet;

    // make request using underlying http lib
    cli->MakeRequest(cri, respRet);

    respRet.GetBody(); // returns http body
    respRet.GetCode(); // returns http code
```