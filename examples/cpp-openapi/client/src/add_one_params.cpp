#include "add_one_params.h"
#include "typefactory.h"
#include "todo_params_common.h"

std::string const AddOneParams::ContentType = "application/io.goswagger.examples.todo-list.v1+json";
std::string const AddOneParams::Method = "POST";
std::string const AddOneParams::PathPattern = "/";

void AddOneParams::WriteParams(std::shared_ptr<IOASClientRequest> req) const
{
    WriteParamsCommon<AddOneParams>(*this, req);

    if (this->Body.has_value())
    {
        std::shared_ptr<Json> j = TypeFactory::NewJson();
        Json::ToJson(j, this->Body.value());
        req->SetBodyParam(j->ToString());
    }
}
