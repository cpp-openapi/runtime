#pragma once

#include "openapi/runtime/string.h"

namespace openapi
{

namespace testutil
{

// can convert from char* to string or wstring
string_t StringT(const char* mbstr);

// TODO: use const expr?
std::string ToStdString(string_t text);

string_t StringT(const wchar_t* mbstr);


} // namespace testutil
} // namespace openapi