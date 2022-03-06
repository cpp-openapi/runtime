#include "gtest/gtest.h"
#include "openapi/runtime/router.h"
#include <thread>
#include <future>
#include <chrono>


using namespace openapi;

TEST(Router, execute) 
{    
    RouteBuilder<bool> b;
    Router<bool> r = b.AddRoute("GET","name/{name}/age/{age}", true)
                .AddRoute("PUT", "hello", false)
                .Build();
    
    {
        PathParamValue ret;
        bool dataRet;
        bool lookUpSuccess = r.LookUp("PUT","hello", ret, dataRet);
        ASSERT_TRUE(lookUpSuccess);
        ASSERT_EQ(0, ret.size());
        ASSERT_FALSE(dataRet);
    }

    {
        PathParamValue ret;
        bool dataRet = true;
        bool lookUpSuccess = r.LookUp("GET", "name/John/age/10", ret, dataRet);
        ASSERT_TRUE(lookUpSuccess);
        ASSERT_EQ(2, ret.size());
        ASSERT_EQ("name", ret[0].first);
        ASSERT_EQ("John", ret[0].second);
        ASSERT_EQ("age", ret[1].first);
        ASSERT_EQ("10", ret[1].second);
        ASSERT_TRUE(dataRet);
    }

}