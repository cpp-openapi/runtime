#include "gtest/gtest.h"
#include "openapi/runtime/request.h"

TEST(Request_test, queryParam) 
{    
    std::shared_ptr<IOASClientRequest> req = std::make_shared<ClientRequestImpl>();

    {
        req->SetQueryParam("hello", 1);
        int ret = 0;
        bool ok = req->GetQueryParam("hello", ret);
        ASSERT_TRUE(ok);
        ASSERT_EQ(1, ret);
    }

    {
        req->SetQueryParam("key", "val");
        std::string ret;
        bool ok = req->GetQueryParam("key", ret);

        ASSERT_TRUE(ok);
        ASSERT_EQ("val", ret);
    }

    {
        std::string ret;
        bool ok = req->GetQueryParam("keyNotExist", ret);
        ASSERT_TRUE(!ok);
    }

    {
        req->SetQueryParam("key1", "val1,val2");

        {
            std::string ret;
            bool ok = req->GetQueryParam("key1", ret);
            ASSERT_TRUE(ok);
            ASSERT_EQ(std::string("val1,val2"), ret);
        }

        // vector value is not splited, client should never insert with ","
        std::vector<std::string> ret;
        bool ok = req->GetQueryParam("key1", ret);
        ASSERT_TRUE(ok);
        std::vector<std::string> expect = {"val1,val2"};
        ASSERT_EQ(expect.size(), ret.size());
        ASSERT_EQ(expect[0],ret[0]);
    }

    {
        std::vector<std::string> data = {"val1", "val2"};
        req->SetQueryParam("key2", data);

        {
            // the first element is chosen
            std::string ret;
            bool ok = req->GetQueryParam("key2", ret);
            ASSERT_TRUE(ok);
            ASSERT_EQ(std::string("val1"), ret);
        }

        std::vector<std::string> ret;
        bool ok = req->GetQueryParam("key2", ret);
        ASSERT_TRUE(ok);
        std::vector<std::string> expect = {"val1", "val2"};
        ASSERT_EQ(expect.size(), ret.size());
        ASSERT_EQ(expect[0],ret[0]);
        ASSERT_EQ(expect[1],ret[1]);
    }
}

TEST(Request_test, pathParam) 
{ 
    std::shared_ptr<IOASClientRequest> req = std::make_shared<ClientRequestImpl>();

    {
        req->SetPathParam("hello", 1);
        int ret = 0;
        bool ok = req->GetPathParam("hello", ret);
        ASSERT_TRUE(ok);
        ASSERT_EQ(1, ret);
    }

    {
        req->SetPathParam("key", "val");
        std::string ret;
        bool ok = req->GetPathParam("key", ret);

        ASSERT_TRUE(ok);
        ASSERT_EQ("val", ret);
    }

    {
        std::string ret;
        bool ok = req->GetPathParam("keyNotExist", ret);
        ASSERT_TRUE(!ok);
    }
}

TEST(Request_test, headerParam) 
{ 
    std::shared_ptr<IOASClientRequest> req = std::make_shared<ClientRequestImpl>();

    {
        req->SetHeaderParam("hello", 1);
        int ret = 0;
        bool ok = req->GetHeaderParam("hello", ret);
        ASSERT_TRUE(ok);
        ASSERT_EQ(1, ret);
    }

    {
        req->SetHeaderParam("key", "val");
        std::string ret;
        bool ok = req->GetHeaderParam("key", ret);

        ASSERT_TRUE(ok);
        ASSERT_EQ("val", ret);
    }

    {
        std::string ret;
        bool ok = req->GetHeaderParam("keyNotExist", ret);
        ASSERT_TRUE(!ok);
    }
}


TEST(Request_test, wideStringRet) 
{ 
    std::shared_ptr<IOASClientRequest> req = std::make_shared<ClientRequestImpl>();
    
    {
        req->SetHeaderParam("key", L"val");
        std::string ret;
        bool ok = req->GetHeaderParam("key", ret);

        ASSERT_TRUE(ok);
        ASSERT_EQ("val", ret);
    }

    {
        req->SetHeaderParam("key2", L"val2");
        std::wstring ret;
        bool ok = req->GetHeaderParam("key2", ret);

        ASSERT_TRUE(ok);
        ASSERT_EQ(L"val2", ret);
    }

    {
        std::wstring ret;
        bool ok = req->GetHeaderParam("keyNotExist", ret);
        ASSERT_TRUE(!ok);
    }
}