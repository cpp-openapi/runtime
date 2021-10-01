#pragma once

#include "request.h"
#include "response.h"

template<typename P, typename R>
R ProcessAPI(const P &params, std::shared_ptr<IClient> cli, AuthInfoWriter auth)
{
    R result;
    std::shared_ptr<IOASClientRequest> cri = std::make_shared<ClientRequestImpl>();
    params.WriteParams(cri);
    
    if (auth)
    {
        // add auth
        auth(cri);
    }

    std::shared_ptr<IOASClientResponse> resp =  std::make_shared<ClientResponseImpl>();

    cli->MakeRequest(*cri, *resp);

    result.ReadResponse(resp);
    return result;
}