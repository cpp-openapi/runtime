#include "openapi/runtime/string.h"
#include "openapi/runtime/strconv.h"
#include <vector>

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

std::vector<std::string> SplitStdString(const std::string &data, const char delimiter)
{
    std::vector<std::string> res;
    std::size_t start = 0;
    std::size_t end = data.find(delimiter);
    while (end != std::string::npos)
    {
        std::string part = data.substr(start, end - start);
        res.push_back(part);
        start = end + 1;
        end = data.find(delimiter, start);
    }
    std::string part = data.substr(start, end);
    res.push_back(part);
    return res;
}

std::string JoinStrings(const std::vector<std::string> & data, const char delimiter)
{
    std::string res;
    for(std::size_t i = 0; i < data.size(); i++)
    {
        res += data[i]; 
        if(i < data.size() - 1)
        {
            res += delimiter;
        }
    }
    return res;
}

} // namespace openapi