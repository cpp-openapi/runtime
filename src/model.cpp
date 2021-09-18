#include "model.h"

void Item::json_deserialize(std::shared_ptr<Json> j){

    if (j->HasKey("id")){
        this->id = (*j)["id"]->GetInt();
    }else{
        this->id = 0;
    }

    if (j->HasKey("description")){
        this->description = (*j)["description"]->GetString();
    }

    // get bool?
    // std::shared_ptr<Json> node = j->GetObj("ok");
}

void Item::to_json(std::shared_ptr<Json> j) const
{
    j->AddMemberInt("id", this->id);
    j->AddMemberString("description", this->description);
}