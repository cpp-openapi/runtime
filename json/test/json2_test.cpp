#include "gtest/gtest.h"
#include <string>
#include "openapi_nlohmann_json2.h"
#include "openapi_rapidjson2.h"
#include <memory>


#ifdef OPENAPI_RAPIDJSON
typedef RapidJson2 Json;
#elif defined(OPENAPI_NLOHMANNJSON)
typedef NlohmannJson2 Json;
#endif

TEST(Json2, GetInt)
{
    Json x;
    x.Parse(R"(
        {
            "str" : "str_val",
            "int" : 1
        }
    )");

    ASSERT_EQ(1, x.GetMember<int>("int"));
    ASSERT_EQ("str_val", x.GetMember<std::string>("str"));
}

TEST(Json2, GetArray)
{
    Json x;
    x.Parse(R"(
        [1,2,3]
        )");
    std::vector<int> nums = x.Get<std::vector<int>>();
    std::vector<int> expect = {1,2,3};
    ASSERT_EQ(expect.size(), nums.size());
    for(int i = 0; i < expect.size(); i++)
    {
        ASSERT_EQ(expect[i],nums[i]);
    }
}

TEST(Json2, GetAndSetStruct)
{
    struct Book
    {
        std::string title;
        int pages;
        void DeserializeJSON(const Json & j)
        {
            this->title = j.GetMember<std::string>("title");
            this->pages = j.GetMember<int>("pages");
        }

        Json SerializeJSON()
        {
            Json j;
            j.AddMember("title", this->title);
            j.AddMember("pages", this->pages);
            return j;
        }
    };

    Json x;
    x.Parse(R"(
        {
            "title" : "MyTitle",
            "pages" : 10
        }
    )");

    Book b = x.Get<Book>();
    ASSERT_EQ("MyTitle", b.title);
    ASSERT_EQ(10, b.pages);

    // serrialize back
    Json x2;
    x2.Set(b);
    
    nlohmann::json r = nlohmann::json::parse(x.ToString());
    nlohmann::json r2 = nlohmann::json::parse(x2.ToString());
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

    x.AddMember("array",expect);
    
    std::vector<int> nums = x.GetMember<std::vector<int>>("array");
    for(int i = 0; i < expect.size(); i++)
    {
        ASSERT_EQ(expect[i],nums[i]);
    }
}