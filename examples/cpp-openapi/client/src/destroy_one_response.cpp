#include "destroy_one_response.h"

#include "typefactory.h"
#include <iostream>

#include "todo_response_common.h"
#include "todo_stream.h"

void DestroyOneResponse::ReadResponse(std::shared_ptr<IOASClientResponse> resp)
{
    ReadResponseCommon<DestroyOneResponse>(*this, resp);
}

std::ostream& operator<<(std::ostream& os, const DestroyOneResponse& resp){
    return WriteResponseToStream(os, resp);
}