#include "destroy_one_params.h"

std::string const DestroyOneParams::ContentType = "application/io.goswagger.examples.todo-list.v1+json";
std::string const DestroyOneParams::Method = "DELETE";
std::string const DestroyOneParams::PathPattern = "/{id}";

void DestroyOneParams::WriteParams(std::shared_ptr<IOASClientRequest> req)
{
    req->SetHeaderParam("Content-Type", DestroyOneParams::ContentType);
    req->SetMethod(DestroyOneParams::Method);
    req->SetPathPattern(DestroyOneParams::PathPattern);
    if (this->id.has_value())
    {
        req->SetPathParam("id", this->id.value());
    }
}