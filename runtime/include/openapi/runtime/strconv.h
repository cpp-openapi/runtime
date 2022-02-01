#pragma once

// #ifndef OPENAPI_RUNTIME_TYPES_STD
// #error openapi/runtime/string.h not included
// #endif

// #include <cstring> // strlen
#include <cwchar>
#include <cassert>
#include <string>

namespace openapi{

std::string MultiByteToWideChar(const wchar_t* mbstr);

std::wstring WideCharToMultiByte(const char* mbstr);



}
