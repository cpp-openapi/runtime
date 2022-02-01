#pragma once

// #include "openapi/runtime/strconv.h"

#include <string>

// indicates this header is included. string_t is defined.
#define OPENAPI_RUNTIME_TYPES_STD 1

#ifndef OPENAPI_CUSTOM_STRING_TYPES
// define default openapi string types

// string type
namespace openapi 
{

#ifdef OPENAPI_UTF16_STRINGS // user wchar

#define OPENAPI_LITERAL(x) L ## #x
typedef std::wstring string_t;

#else

#define OPENAPI_LITERAL(x) #x

typedef std::string string_t;

typedef wchar_t char_t;

#endif // OPENAPI_UTF16_STRINGS

// can convert from char* to string or wstring
string_t StringT(const char* mbstr);

// TODO: use const expr?
std::string ToStdString(string_t text);

string_t StringT(const wchar_t* mbstr);


} // namespace openapi

#endif // OPENAPI_CUSTOM_STRING_TYPES
