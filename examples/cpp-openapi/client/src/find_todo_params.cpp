#include "find_todo_params.h"
#include "todo_params_common.h"

std::string const FindTodosParams::ContentType = "application/io.goswagger.examples.todo-list.v1+json";
std::string const FindTodosParams::Method = "GET";
std::string const FindTodosParams::PathPattern = "/";

void FindTodosParams::WriteParams(std::shared_ptr<IOASClientRequest> req) const
{
    WriteParamsCommon<FindTodosParams>(*this, req);

    if (this->limit.has_value()){
        req->SetQueryParam<int>("limit", this->limit.value());
    }
    if (this->since.has_value()){
        req->SetQueryParam<int>("since", this->since.value());
    }
}