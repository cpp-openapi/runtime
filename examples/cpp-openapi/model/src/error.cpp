#include "error.h"

void Error::SerializeJSON(std::shared_ptr<Json> j) const
{
    if(this->code.has_value())
    {
        Json::AddMember<int>(j,"code",this->code.value());
    }

    if(this->message.has_value())
    {
        Json::AddMember<std::string>(j,"message",this->message.value());
    }
}
void Error::DeserializeJSON(std::shared_ptr<Json> j)
{
    if (j->HasKey("code"))
    {
        this->code = Json::GetMember<int>(j, "code");
    }

    if (j->HasKey("message"))
    {
        this->message = Json::GetMember<std::string>(j, "message");
    }
}