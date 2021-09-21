#include "gtest/gtest.h"
#include <string>

struct Person
{
    std::string name;
    int age;
};

TEST(ExampleParse, Ok) {
    const char * ptr = R"(
        {
            "name": "John",
            "age" : 10
        }
    )";

    
}