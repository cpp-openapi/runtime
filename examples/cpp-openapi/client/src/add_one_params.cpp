#include "add_one_params.h"
#include "typefactory.h"

void AddOneParams::WriteParams(std::shared_ptr<IOASClientRequest> req)
{
    if (this->Body.has_value())
    {
        std::shared_ptr<Json> j = TypeFactory::NewJson();
        Json::ToJson(j, this->Body.value());
        req->SetBodyParam(j->ToString());
        //std::cout << "debug body: " << req->GetBody() << std::endl;
    }
}
