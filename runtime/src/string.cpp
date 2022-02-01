#include "openapi/runtime/string.h"
#include "openapi/runtime/strconv.h"

namespace openapi{

// can convert from char* to string or wstring
string_t StringT(const char* mbstr)
{
#ifdef OPENAPI_UTF16_STRINGS
    return WideCharToMultiByte(mbstr);
#else  // OPENAPI_UTF16_STRINGS
    return std::string(mbstr);
#endif // OPENAPI_UTF16_STRINGS
}

// TODO: use const expr?
std::string ToStdString(string_t text)
{
#ifdef OPENAPI_UTF16_STRINGS
    return MultiByteToWideChar(text.c_str());
#else  // OPENAPI_UTF16_STRINGS
    return text;
#endif // OPENAPI_UTF16_STRINGS 
}

string_t StringT(const wchar_t* mbstr)
{
#ifdef OPENAPI_UTF16_STRINGS
    return string_t(mbstr);
#else  // OPENAPI_UTF16_STRINGS
    return MultiByteToWideChar(mbstr);
#endif // OPENAPI_UTF16_STRINGS
}

} // namespace openapi