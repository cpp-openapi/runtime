#include "gtest/gtest.h"
#include <string>
#include <memory>
#include "openapi/runtime/strconv.h"

#include "openapi/json/macro.h"
#include <nlohmann/json.hpp> // for raw json compare

#ifdef OPENAPI_RAPIDJSON
#include "openapi/json/rapid.h"
typedef RapidJson Json;
#elif defined(OPENAPI_NLOHMANNJSON)
#include "openapi/json/nlohmann.h"
typedef NlohmannJson Json;
#endif

openapi::string_t personJson = openapi::StringT(R"(
    {
        "name": "John",
        "age" : 10,
        "optional_id": "xyz",
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
)");

struct Address
{
    openapi::string_t state;
    openapi::string_t city;
    OPENAPI_JSON_CONVERT_FUNCS_DECLARE
};
OPENAP_JSON_CONVERT_FUNCS(Address, state, city)

struct Company
{
    openapi::string_t name;
    std::shared_ptr<Address> location;
    OPENAPI_JSON_CONVERT_FUNCS_DECLARE
};
OPENAP_JSON_CONVERT_FUNCS(Company, name, location)

struct Order
{
    int id;
    OPENAPI_JSON_CONVERT_FUNCS_DECLARE
};
OPENAP_JSON_CONVERT_FUNCS(Order, id)

struct Person
{
    openapi::string_t name;
    int age;
    std::optional<openapi::string_t> optional_id;
    std::vector<Address> address;
    Company company;
    std::vector<int> project_ids;
    std::vector<openapi::string_t> project_names;
    std::vector<std::shared_ptr<Order>> orders;
    OPENAPI_JSON_CONVERT_FUNCS_DECLARE
};
OPENAP_JSON_CONVERT_FUNCS(Person, name, age, optional_id, address, company, project_ids, project_names, orders)

TEST(Json, Deserialize)
{
    Json j;
    j.Parse(personJson);

    Person p;
    p.FromJSON(j);

    ASSERT_EQ(OPENAPI_LITERAL(John), p.name);
    ASSERT_EQ(p.age, 10);
    
    ASSERT_TRUE(p.optional_id.has_value());
    ASSERT_EQ(OPENAPI_LITERAL(xyz), p.optional_id.value());

    ASSERT_EQ(2, p.address.size());
    Address expectAddr1 = {
        openapi::StringT("CA"),
        openapi::StringT("Los Angeles")};
    Address expectAddr2 = {
        openapi::StringT("WA"),
        openapi::StringT("Seattle")};

    Address actualAddr1 = p.address[0];
    Address actualAddr2 = p.address[1];

    ASSERT_EQ(expectAddr1.state, actualAddr1.state);
    ASSERT_EQ(expectAddr1.city, actualAddr1.city);
    ASSERT_EQ(expectAddr2.state, actualAddr2.state);
    ASSERT_EQ(expectAddr2.city, actualAddr2.city);
    // ASSERT_EQ(expectAddr1, actualAddr1);

    ASSERT_EQ(openapi::StringT("Costco"), p.company.name);
    ASSERT_EQ(openapi::StringT("OR"), p.company.location->state);
    ASSERT_EQ(openapi::StringT("Portland"), p.company.location->city);

    ASSERT_EQ(3, p.project_ids.size());
    std::vector<int> expected_project_ids = {1, 2, 3};
    for (int i = 0; i < expected_project_ids.size(); i++)
    {
        ASSERT_EQ(expected_project_ids[i], p.project_ids[i]);
    }

    ASSERT_EQ(2, p.project_names.size());
    std::vector<openapi::string_t> expected_project_names = {openapi::StringT("project1"), openapi::StringT("project2")};
    for (int i = 0; i < expected_project_names.size(); i++)
    {
        ASSERT_EQ(expected_project_names[i], p.project_names[i]);
    }

    ASSERT_EQ(2, p.orders.size());
    ASSERT_EQ(11, p.orders[0]->id);
    ASSERT_EQ(12, p.orders[1]->id);
}

TEST(Json, Serialize)
{
    Person p;
    p.name = openapi::StringT("John");
    p.age = 10;
    p.address = {
        {openapi::StringT("CA"), openapi::StringT("Los Angeles")},
        {openapi::StringT("WA"), openapi::StringT("Seattle")}};

    //     "name" : "Costco",
    //     "location" : {
    //         "state" : "OR",
    //         "city" : "Portland"
    //     }
    p.company.name = openapi::StringT("Costco");
    p.company.location = std::make_shared<Address>();
    p.company.location->state = openapi::StringT("OR");
    p.company.location->city = openapi::StringT("Portland");

    //  "project_ids" : [1,2,3],
    //  "project_names" : ["project1","project2"],
    p.project_ids = {1, 2, 3};
    p.project_names = {openapi::StringT("project1"), openapi::StringT("project2")};

    // "orders" : [{"id":11},{"id":12}]
    p.orders = {std::make_shared<Order>(), std::make_shared<Order>()};
    p.orders[0]->id = 11;
    p.orders[1]->id = 12;

    Json j;
    p.ToJSON(j);

    ASSERT_EQ(p.name, j.GetMember<openapi::string_t>(openapi::StringT("name")));
    ASSERT_EQ(p.age, j.GetMember<int>(openapi::StringT("age")));

    // address
    std::vector<Address> &addressExpect = p.address;
    std::vector<Address> addressResult = j.GetMember<std::vector<Address>>(openapi::StringT("address"));
    ASSERT_EQ(addressExpect.size(), addressResult.size());
    ASSERT_EQ(addressExpect[0].state, addressResult[0].state);
    ASSERT_EQ(addressExpect[0].city, addressResult[0].city);
    ASSERT_EQ(addressExpect[1].state, addressResult[1].state);
    ASSERT_EQ(addressExpect[0].city, addressResult[0].city);

    // company
    Company companyExpected = p.company;
    Company companyResult = j.GetMember<Company>(openapi::StringT("company"));
    ASSERT_EQ(companyExpected.name, companyResult.name);

    // array
    ASSERT_EQ(p.project_ids, j.GetMember<std::vector<int>>(openapi::StringT("project_ids")));
    ASSERT_EQ(p.project_names, j.GetMember<std::vector<openapi::string_t>>(openapi::StringT("project_names")));

    // orders
    std::vector<std::shared_ptr<Order>> &orderExpected = p.orders;
    std::vector<std::shared_ptr<Order>> ordersResult = j.GetMember<std::vector<std::shared_ptr<Order>>>(openapi::StringT("orders"));
    ASSERT_EQ(orderExpected.size(), ordersResult.size());
    ASSERT_EQ(orderExpected[0]->id, ordersResult[0]->id);
    ASSERT_EQ(orderExpected[1]->id, ordersResult[1]->id);
}

TEST(Json, deserialize_identity)
{
    Json j;
    j.Parse(personJson);
    Person p;
    p.FromJSON(j);

    Json j2;
    p.ToJSON(j2);

    nlohmann::json jExpect = nlohmann::json::parse(personJson);
    nlohmann::json jResult = nlohmann::json::parse(j2.ToString());
    // std::cout << "debug" << openapi::ToStdString(j2.ToString()) << std::endl;
    ASSERT_TRUE(jExpect == jResult);
}