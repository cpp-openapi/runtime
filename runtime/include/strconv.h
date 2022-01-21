#pragma once
#include "runtime_types.h"

#include <cstring> // strlen

namespace openapi{

// can convert from char* to string or wstring
static string_t StringT(const char* text)
{
#ifdef OPENAPI_UTF16_STRINGS
    const size_t size = std::strlen(text);
        std::wstring wstr;
        if (size > 0) {
            wstr.resize(size);
            std::mbstowcs(&wstr[0], text, size);
        }
        return static_cast<string_t>(wstr);
#else
    return std::string(text);
#endif
}

// TODO: use const expr?
static std::string ToStdString(string_t text)
{
#ifdef OPENAPI_UTF16_STRINGS
    const size_t size = text.size();
        std::string str;
        if (size > 0) {
            str.resize(size);
            std::wcstombs(&str[0], text.c_str(), size);
        }
        return str;
#else
    return text;
#endif
}

}
