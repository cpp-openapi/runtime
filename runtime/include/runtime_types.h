#pragma once

#include <optional>

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