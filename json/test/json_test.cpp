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
};

struct Order
{
    int id;
    void DeserializeJSON(std::shared_ptr<Json> j)
    {
        this->id = Json::GetMember<int>(j, "id");
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