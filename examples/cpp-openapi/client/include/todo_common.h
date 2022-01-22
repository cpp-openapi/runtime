#pragma once

#include "openapi/runtime/request.h"
#include "openapi/runtime/response.h"
#include "openapi/runtime/executor.h"

// returns future of response
template<typename P, typename R>
std::future<R> ProcessAPI(const P &params, std::shared_ptr<IClient> cli, AuthInfoWriter auth)
{
    std::shared_ptr<IOASClientRequest> req = std::make_shared<ClientRequestImpl>();
    params.WriteParams(req);
    
    if (auth)
    {
        // add auth
        auth(req);
    }

    std::shared_future<std::shared_ptr<IOASClientResponse>> respFuture = cli->Do(req).share();

    std::shared_ptr<std::promise<R>> p = std::make_shared<std::promise<R>>();

    Executor::GetInstance().Submit([p, respFuture]() {
        try
        {
            // get future response
            std::shared_ptr<IOASClientResponse> resp = respFuture.get();
            R result;
            result.ReadResponse(resp);
            p->set_value(result);
        }
        catch([[maybe_unused]] const std::exception &e)
        {
            try
            {
                p->set_exception(std::current_exception());
            } catch(...) {}
        }
    });
    return p->get_future();
}