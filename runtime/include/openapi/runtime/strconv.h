#pragma once
// #include "openapi/runtime/runtime_types.h"

#ifndef OPENAPI_RUNTIME_TYPES_STD
#error runtime_types.h not included
#endif

// #include <cstring> // strlen
#include <cwchar>
#include <cassert>
#include <string>

namespace openapi{

static std::string FromWStr(const wchar_t* mbstr)
{
    std::size_t size{};
    std::size_t size2{}; 
    std::string str;
    std::mbstate_t state = std::mbstate_t();
    const wchar_t * wstr = mbstr;
#ifdef WIN32
    ::wcsrtombs_s(&size, nullptr, 0/*dest cap*/, &wstr, 0, &state);
#else
    size = wcsrtombs(NULL, &wstr, 0, &state);
#endif
    if (size <= 0) {
        return str;
    }
    str.resize(size);
#ifdef WIN32
    ::wcsrtombs_s(&size2, &str[0], size/*dest cap*/, &wstr, size, &state);
#else
    size2 = wcsrtombs(&str[0], &wstr, size, &state);
#endif
    assert(size == size2);

#ifdef WIN32
    // strip the redundant null terminator
    if(str[size-1] == '\0')
    {
        // terminator is redundant.
        str.resize(size-1);
    }
#endif
    return str;
}

static std::wstring FromStr(const char* mbstr)
{
    std::size_t size{};
    std::size_t size2{};
    std::mbstate_t state = std::mbstate_t();
#ifdef WIN32 
    // windows we have the safe convert function
    // will count null terminator in the size.
    ::mbsrtowcs_s(&size, nullptr, 0 /*dst max size*/,  &mbstr, 0, &state);
#else
    size = std::mbsrtowcs(nullptr, &mbstr, 0, &state);
#endif
    std::wstring wstr;
    if(size <= 0)
    {
        return wstr;
    }
    wstr.resize(size); // wtr has null terminator by itself.
#ifdef WIN32
    ::mbsrtowcs_s(&size2, &wstr[0], size  /*dst max size*/ , &mbstr, size, &state);
#else
    size2 = std::mbsrtowcs(&wstr[0], &mbstr, size, &state);
#endif
    assert(size2 == size);

#ifdef WIN32
    if(wstr[size-1] == L'\0')
    {
        // terminator is redundant.
        wstr.resize(size-1);
    }
#endif
    return wstr;
}

// can convert from char* to string or wstring
static string_t StringT(const char* mbstr)
{
#ifdef OPENAPI_UTF16_STRINGS
    return FromStr(mbstr);
#else  // OPENAPI_UTF16_STRINGS
    return std::string(mbstr);
#endif // OPENAPI_UTF16_STRINGS
}

// TODO: use const expr?
static std::string ToStdString(string_t text)
{
#ifdef OPENAPI_UTF16_STRINGS
    return FromWStr(text.c_str());
#else  // OPENAPI_UTF16_STRINGS
    return text;
#endif // OPENAPI_UTF16_STRINGS 
}

static string_t StringT(const wchar_t* mbstr)
{
#ifdef OPENAPI_UTF16_STRINGS
    return string_t(mbstr);
#else  // OPENAPI_UTF16_STRINGS
    return FromWStr(mbstr);
#endif // OPENAPI_UTF16_STRINGS     
}

}
