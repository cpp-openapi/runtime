#include "gtest/gtest.h"
#include <string>

#include <nlohmann/json.hpp> // for raw json compare
#include <memory>

// custom string types we skip std types impl
#ifndef OPENAPI_CUSTOM_STRING_TYPES
#include "openapi/runtime/strconv.h"
#include "openapi/runtime/string.h"
#endif

#include "openapi/json/macro.h"

#ifndef OPENAPI_CUSTOM_JSON // custom json may use this test

#ifdef OPENAPI_RAPIDJSON
#include "openapi/json/rapid.h"
typedef RapidJson Json;
#elif defined(OPENAPI_NLOHMANNJSON)
#include "openapi/json/nlohmann.h"
typedef NlohmannJson Json;
#endif

#endif // OPENAPI_CUSTOM_JSON

TEST(Json2, GetInt)
{
    Json x;
    x.Parse(openapi::StringT(R"(
        {
            "str" : "str_val",
            "int" : 1
        }
    )"));

    ASSERT_EQ(1, x.GetMember<int>(openapi::StringT("int")));
    ASSERT_EQ(openapi::ToStdString(openapi::StringT("str_val")), openapi::ToStdString(x.GetMember<openapi::string_t>(openapi::StringT("str"))));
}

TEST(Json2, GetArray)
{
    Json x;
    x.Parse(openapi::StringT(R"(
        [1,2,3]
        )"));
    std::vector<int> nums = x.Get<std::vector<int>>();
    std::vector<int> expect = {1,2,3};
    ASSERT_EQ(expect.size(), nums.size());
    for(int i = 0; i < expect.size(); i++)
    {
        ASSERT_EQ(expect[i],nums[i]);
    }
}

struct Book
{
    openapi::string_t title;
    int pages;
    OPENAPI_JSON_CONVERT_FUNCS_DECLARE
};
OPENAP_JSON_CONVERT_FUNCS(Book, title, pages)

TEST(Json2, GetAndSetStruct)
{
    Json x;
    x.Parse(openapi::StringT(R"(
        {
            "title" : "MyTitle",
            "pages" : 10
        }
    )"));

    Book b = x.Get<Book>();
    ASSERT_EQ(openapi::ToStdString(openapi::StringT("MyTitle")), openapi::ToStdString(b.title));
    ASSERT_EQ(10, b.pages);

    // serrialize back
    Json x2;
    x2.Set(b);
    
    nlohmann::json r = nlohmann::json::parse(openapi::ToStdString(x.ToString()));
    nlohmann::json r2 = nlohmann::json::parse(openapi::ToStdString(x2.ToString()));
    ASSERT_TRUE(r == r2);
}

TEST(Json2, SetArray)
{
    Json x;
    std::vector<int> expect = {1,2,3};

    x.Set(expect);
    
    std::vector<int> nums = x.Get<std::vector<int>>();
    for(int i = 0; i < expect.size(); i++)
    {
        ASSERT_EQ(expect[i],nums[i]);
    }
}

TEST(Json2, SetArrayMember)
{
    Json x;
    std::vector<int> expect = {1,2,3};

    x.AddMember(openapi::StringT("array"),expect);
    
    std::vector<int> nums = x.GetMember<std::vector<int>>(openapi::StringT("array"));
    for(int i = 0; i < expect.size(); i++)
    {
        ASSERT_EQ(expect[i],nums[i]);
    }
}