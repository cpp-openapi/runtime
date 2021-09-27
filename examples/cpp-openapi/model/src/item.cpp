#include "item.h"

void Item::SerializeJSON(std::shared_ptr<Json> j) const
{
    if(this->id.has_value())
    {
        Json::AddMember<int>(j,"id",this->id.value());
    }

    if(this->description.has_value())
    {
        Json::AddMember<std::string>(j,"description",this->description.value());
    }
    //j->AddMemberString("description", this->description);
}


void Item::DeserializeJSON(std::shared_ptr<Json> j){

    if (j->HasKey("id"))
    {
        this->id = Json::GetMember<int>(j, "id");
    }

    if (j->HasKey("description"))
    {
        this->description = Json::GetMember<std::string>(j, "description");
    }

    // get bool?
    // std::shared_ptr<Json> node = j->GetObj("ok");
}
