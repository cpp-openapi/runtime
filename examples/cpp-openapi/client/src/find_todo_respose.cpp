#include "find_todo_response.h"
#include "typefactory.h"
#include "todo_response_common.h"
#include "todo_stream.h"

void FindTodoResponse::ReadResponse(std::shared_ptr<IOASClientResponse> resp)
{
    ReadResponseCommon<FindTodoResponse>(*this, resp);
}

std::ostream& operator<<(std::ostream& os, const FindTodoResponse& resp){
    return WriteResponseToStream(os, resp);
}