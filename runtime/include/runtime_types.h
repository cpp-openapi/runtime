#pragma once

#include <optional>
#include <memory>
#include <vector>

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