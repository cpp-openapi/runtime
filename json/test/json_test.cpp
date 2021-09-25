#include "gtest/gtest.h"
#include <string>
#include "openapi_nlohmann_json.h"
#include "openapi_rapidjson.h"
#include <memory>

const char * personJson = R"(
    {
        "name": "John",
        "age" : 10,
        "address" : [
            {
                "state" : "CA",
                "city" : "Los Angeles"
            },
            {
                "state" : "WA",
                "city" : "Seattle"
            }
        ],
        "company" : {
            "name" : "Costco",
            "location" : {
                "state" : "OR",
                "city" : "Portland"
            }
        },
        "project_ids" : [1,2,3],
        "project_names" : ["project1","project2"],
        "orders" : [{"id":11},{"id":12}]
    }
)";

struct Address
{
    std::string state;
    std::string city;
    void DeserializeJSON(std::shared_ptr<Json> j)
    {
        this->state = Json::GetMember<std::string>(j, "state");
        this->city = Json::GetMember<std::string>(j, "city");
    }

    void SerializeJSON(std::shared_ptr<Json> j)
    {
        Json::AddMember<std::string>(j, "state", this->state);
        Json::AddMember<std::string>(j, "city", this->city);
    }
};

struct Company
{
    std::string name;
    std::shared_ptr<Address> location;
    void DeserializeJSON(std::shared_ptr<Json> j)
    {
        this->name = Json::GetMember<std::string>(j, "name");
        this->location = Json::GetMember<std::shared_ptr<Address>>(j, "location");
    }

    void SerializeJSON(std::shared_ptr<Json> j)
    {
        Json::AddMember<std::string>(j, "name", this->name);
        Json::AddMember<std::shared_ptr<Address>>(j, "location", this->location);
    }
};

struct Order
{
    int id;
    void DeserializeJSON(std::shared_ptr<Json> j)
    {
        this->id = Json::GetMember<int>(j, "id");
    }
    void SerializeJSON(std::shared_ptr<Json> j)
    {
        Json::AddMember<int>(j, "id", this->id);
    }
};

struct Person
{
    std::string name;
    int age;
    std::vector<Address> address;
    Company company;
    std::vector<int> project_ids;
    std::vector<std::string> project_names;
    std::vector<std::shared_ptr<Order>> orders;
    void DeserializeJSON(std::shared_ptr<Json> j)
    {
        this->name = Json::GetMember<std::string>(j, "name");
        this->age = Json::GetMember<int>(j, "age");
        this->address = Json::GetMember<std::vector<Address>>(j, "address");
        this->company = Json::GetMember<Company>(j, "company");

        // primitive array
        this->project_ids = Json::GetMember<std::vector<int>>(j, "project_ids");
        this->project_names = Json::GetMember<std::vector<std::string>>(j, "project_names");

        // ptr array
        this->orders = Json::GetMember<std::vector<std::shared_ptr<Order>>>(j, "orders");
    }

    void SerializeJSON(std::shared_ptr<Json> j)
    {
        Json::AddMember<std::string>(j, "name", this->name);
        Json::AddMember<int>(j, "age", this->age);
        Json::AddMember<std::vector<Address>>(j, "address", this->address);
        Json::AddMember<Company>(j, "company", this->company);

        Json::AddMember<std::vector<int>>(j, "project_ids", this->project_ids);
        Json::AddMember<std::vector<std::string>>(j, "project_names", this->project_names);
        Json::AddMember<std::vector<std::shared_ptr<Order>>>(j, "orders", this->orders);
    }
};

void testJsonImpl(std::shared_ptr<Json> j)
{
    Person p;
    p.DeserializeJSON(j);

    ASSERT_EQ("John", p.name);
    ASSERT_EQ(p.age, 10);
    //ASSERT_TRUE(false);

    ASSERT_EQ(2, p.address.size());
    Address expectAddr1 = {
        "CA",
        "Los Angeles"
    };
    Address expectAddr2 = {
        "WA",
        "Seattle"
    };

    Address actualAddr1 = p.address[0];
    Address actualAddr2 = p.address[1];

    ASSERT_EQ(expectAddr1.state, actualAddr1.state);
    ASSERT_EQ(expectAddr1.city, actualAddr1.city);
    ASSERT_EQ(expectAddr2.state, actualAddr2.state);
    ASSERT_EQ(expectAddr2.city, actualAddr2.city);
    // ASSERT_EQ(expectAddr1, actualAddr1);

    ASSERT_EQ("Costco", p.company.name);
    ASSERT_EQ("OR", p.company.location->state);
    ASSERT_EQ("Portland", p.company.location->city);

    ASSERT_EQ(3, p.project_ids.size());
    std::vector<int> expected_project_ids = {1,2,3};
    for(int i = 0; i < expected_project_ids.size(); i++)
    {
        ASSERT_EQ(expected_project_ids[i],p.project_ids[i]);
    }

    ASSERT_EQ(2, p.project_names.size());
    std::vector<std::string> expected_project_names = {"project1","project2"};
    for(int i = 0; i < expected_project_names.size(); i++)
    {
        ASSERT_EQ(expected_project_names[i],p.project_names[i]);
    }

    ASSERT_EQ(2,p.orders.size());
    ASSERT_EQ(11,p.orders[0]->id);
    ASSERT_EQ(12,p.orders[1]->id);
}

TEST(Json, nlohmannjson) {    
    std::shared_ptr<Json> j = std::make_shared<NlohmannJson>();
    j->SetJson(personJson);
    testJsonImpl(j);
}

TEST(Json, rapidjson)
{
    std::shared_ptr<Json> j = std::make_shared<RapidJson>();
    j->SetJson(personJson);
    testJsonImpl(j);
}


void testJsonSerialize(std::shared_ptr<Json> j)
{
   Person p;
    p.name = "John";
    p.age = 10;
    p.address = {
        {"CA","Los Angeles"},
        {"WA", "Seattle"}
    };

//     "name" : "Costco",
//     "location" : {
//         "state" : "OR",
//         "city" : "Portland"
//     }
    p.company.name = "Costco";
    p.company.location = std::make_shared<Address>();
    p.company.location->state = "OR";
    p.company.location->city = "Portland";

//  "project_ids" : [1,2,3],
//  "project_names" : ["project1","project2"],
    p.project_ids = {1,2,3};
    p.project_names = {"project1","project2"};

// "orders" : [{"id":11},{"id":12}]
    p.orders = {std::make_shared<Order>(), std::make_shared<Order>()};
    p.orders[0]->id = 11;
    p.orders[1]->id = 12;


    p.SerializeJSON(j);

    ASSERT_EQ(p.name, Json::GetMember<std::string>(j, "name"));
    ASSERT_EQ(p.age, Json::GetMember<int>(j, "age"));

    // address
    std::vector<Address> &addressExpect = p.address;
    std::vector<Address> addressResult = Json::GetMember<std::vector<Address>>(j, "address");
    ASSERT_EQ(addressExpect.size(), addressResult.size());
    ASSERT_EQ(addressExpect[0].state, addressResult[0].state);
    ASSERT_EQ(addressExpect[0].city, addressResult[0].city);
    ASSERT_EQ(addressExpect[1].state, addressResult[1].state);
    ASSERT_EQ(addressExpect[0].city, addressResult[0].city);

    // company
    Company companyExpected = p.company;
    Company companyResult = Json::GetMember<Company>(j, "company");
    ASSERT_EQ(companyExpected.name, companyResult.name);

    // array
    ASSERT_EQ(p.project_ids, Json::GetMember<std::vector<int>>(j, "project_ids"));
    ASSERT_EQ(p.project_names, Json::GetMember<std::vector<std::string>>(j, "project_names"));

    // orders
    std::vector<std::shared_ptr<Order>> & orderExpected = p.orders;
    std::vector<std::shared_ptr<Order>> ordersResult =  Json::GetMember<std::vector<std::shared_ptr<Order>>>(j, "orders");
    ASSERT_EQ(orderExpected.size(), ordersResult.size());
    ASSERT_EQ(orderExpected[0]->id, ordersResult[0]->id);
    ASSERT_EQ(orderExpected[1]->id, ordersResult[1]->id);
}

TEST(Json, nolhmannjson_serialize)
{
    std::shared_ptr<NlohmannJson> j = std::make_shared<NlohmannJson>();
    testJsonSerialize(j);
}

TEST(Json, rapidjson_serialize)
{
    std::shared_ptr<RapidJson> j = std::make_shared<RapidJson>();  
    testJsonSerialize(j);
}

TEST(Json, nolhmannjson_serialize_deserialize_identity)
{
    std::shared_ptr<Json> j = std::make_shared<NlohmannJson>();
    j->SetJson(personJson);
    Person p;
    p.DeserializeJSON(j);

    std::shared_ptr<Json> j2 = std::make_shared<NlohmannJson>();
    p.SerializeJSON(j2);

    nlohmann::json jExpect = nlohmann::json::parse(personJson);
    nlohmann::json jResult = nlohmann::json::parse(j2->ToString());
    ASSERT_TRUE(jExpect == jResult);
}

TEST(Json, rapidjson_serialize_deserialize_identity)
{
    std::shared_ptr<Json> j = std::make_shared<RapidJson>();
    j->SetJson(personJson);
    Person p;
    p.DeserializeJSON(j);

    std::shared_ptr<Json> j2 = std::make_shared<RapidJson>();
    p.SerializeJSON(j2);

    rapidjson::Document jExpect;
    jExpect.Parse(personJson);
    rapidjson::Document jResult;
    jResult.Parse(j2->ToString().c_str());
    ASSERT_TRUE(jExpect == jResult);
}