#include "gtest/gtest.h"
#include "openapi/runtime/runtime_types.h"
#include "openapi/runtime/strconv.h"

TEST(StrConv_test, basic) {
#ifdef OPENAPI_UTF16_STRINGS
        // std::mbstate_t state = std::mbstate_t();
        // std::size_t size;
        // const char * buf = "";
        // ::mbsrtowcs_s(&size, nullptr, 0 /*dst max size*/, &buf, 0, &state);
        // ASSERT_EQ(1, size); // counts the null terminator

        // const char * mbstr = "hi";
        // std::mbstate_t state = std::mbstate_t();
        // std::size_t size = std::mbsrtowcs(nullptr, &mbstr, 0, &state);
        // ASSERT_EQ(2, size);

        ASSERT_EQ(L"", openapi::StringT(""));
        ASSERT_EQ(L"hi", openapi::StringT("hi"));

        ASSERT_EQ(std::string(""), openapi::ToStdString(L""));
        ASSERT_EQ(std::string("hi"), openapi::ToStdString(L"hi"));
#else
        ASSERT_EQ("", openapi::StringT(""));
        ASSERT_EQ("hi", openapi::StringT("hi"));

        ASSERT_EQ(std::string(""), openapi::ToStdString(""));
        ASSERT_EQ(std::string("hi"), openapi::ToStdString("hi"));
#endif
}
