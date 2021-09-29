#include "find_todo_params.h"


void FindTodosParams::WriteParams(std::shared_ptr<IOASClientRequest> req){
    if (this->limit.has_value()){
        req->SetQueryParam<int>("limit", this->limit.value());
    }
    if (this->since.has_value()){
        req->SetQueryParam<int>("since", this->since.value());
    }
}