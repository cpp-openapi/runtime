#include "add_one_response.h"
#include "typefactory.h"
#include <string>
#include <iostream>
#include "todo_response_common.h"
#include "todo_stream.h"

void AddOneResponse::ReadResponse(std::shared_ptr<IOASClientResponse> resp)
{
    ReadResponseCommon<AddOneResponse>(*this, resp);
}

std::ostream& operator<<(std::ostream& os, const AddOneResponse& resp){
    return WriteResponseToStream(os, resp);
}