#pragma once

#include <optional>
#include <memory>
#include <vector>

#include <string>

// indicates this header is included. string_t is defined.
#define OPENAPI_RUNTIME_TYPES_STD 1

// remove optional
template<typename T>
struct remove_optional
{
    typedef T type;
};

template<typename T>
struct remove_optional<std::optional<T>>
{
    typedef typename remove_optional<T>::type type;
};

// is optional
template<typename T> struct is_optional : std::false_type {};
template<typename T> struct is_optional<std::optional<T>> : std::true_type {};

// is shared ptr
template<typename T> struct is_shared_ptr : std::false_type {};
template<typename T> struct is_shared_ptr<std::shared_ptr<T>> : std::true_type {};

// remove shared ptr
template<typename T>
struct remove_shared_ptr
{
    typedef T type;
};

template<typename T>
struct remove_shared_ptr<std::shared_ptr<T>>
{
    typedef typename remove_shared_ptr<T>::type type;
};

// detect vector type
template<typename T> struct is_vector : public std::false_type {};
template<typename T, typename A>
struct is_vector<std::vector<T, A>> : public std::true_type {};


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

} // namespace openapi

#endif // OPENAPI_CUSTOM_STRING_TYPES
