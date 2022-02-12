#include "gtest/gtest.h"
#include "openapi/runtime/router.h"
#include <thread>
#include <future>
#include <chrono>


using namespace openapi;

TEST(Router, execute) 
{    
    RouteBuilder b;
    Router r = b.AddRoute("name/{name}/age/{age}")
                .AddRoute("hello")
                .Build();
    
    {
        PathParamValue ret;
        bool lookUpSuccess = r.LookUp("hello", ret);
        ASSERT_TRUE(lookUpSuccess);
        ASSERT_EQ(0, ret.size());
    }

    {
        PathParamValue ret;
        bool lookUpSuccess = r.LookUp("name/John/age/10", ret);
        ASSERT_TRUE(lookUpSuccess);
        ASSERT_EQ(2, ret.size());
        ASSERT_EQ("name", ret[0].first);
        ASSERT_EQ("John", ret[0].second);
        ASSERT_EQ("age", ret[1].first);
        ASSERT_EQ("10", ret[1].second);
    }

}