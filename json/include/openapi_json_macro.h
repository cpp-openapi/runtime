#pragma once

#include "runtime_types.h"

// Expand forces msvc to expand arg, where gcc automatically expands recursively.
#define OPENAPI_EXPAND(x) x

// Call f with x, and recurse
// OPENAPI_CALL_WITH_ARG_i(f,x, ...) means call f with x and then call f with the rest element in
// varidic list.
// (x, ...) must have i elements in total
//
#define OPENAPI_CALL_WITH_ARG_0(f)
#define OPENAPI_CALL_WITH_ARG_1(f, x) f(x) 
#define OPENAPI_CALL_WITH_ARG_2(f, x, ...) f(x) OPENAPI_EXPAND(OPENAPI_CALL_WITH_ARG_1(f, __VA_ARGS__))
#define OPENAPI_CALL_WITH_ARG_3(f, x, ...) f(x) OPENAPI_EXPAND(OPENAPI_CALL_WITH_ARG_2(f, __VA_ARGS__))
#define OPENAPI_CALL_WITH_ARG_4(f, x, ...) f(x) OPENAPI_EXPAND(OPENAPI_CALL_WITH_ARG_3(f, __VA_ARGS__))
#define OPENAPI_CALL_WITH_ARG_5(f, x, ...) f(x) OPENAPI_EXPAND(OPENAPI_CALL_WITH_ARG_4(f, __VA_ARGS__))
#define OPENAPI_CALL_WITH_ARG_6(f, x, ...) f(x) OPENAPI_EXPAND(OPENAPI_CALL_WITH_ARG_5(f, __VA_ARGS__))
#define OPENAPI_CALL_WITH_ARG_7(f, x, ...) f(x) OPENAPI_EXPAND(OPENAPI_CALL_WITH_ARG_6(f, __VA_ARGS__))
#define OPENAPI_CALL_WITH_ARG_8(f, x, ...) f(x) OPENAPI_EXPAND(OPENAPI_CALL_WITH_ARG_7(f, __VA_ARGS__))
#define OPENAPI_CALL_WITH_ARG_9(f, x, ...) f(x) OPENAPI_EXPAND(OPENAPI_CALL_WITH_ARG_8(f, __VA_ARGS__))
#define OPENAPI_CALL_WITH_ARG_10(f, x, ...) f(x) OPENAPI_EXPAND(OPENAPI_CALL_WITH_ARG_9(f, __VA_ARGS__))
// Can add more

// OPENAPI_GET_MACRO(_0,__VA_ARGS__, xxx) intends to get the OPENAPI_CALL_WITH_ARG_i where i = len(__VA_ARGS__)
// OPENAPI_FOR_EACH(f, ...) applies f on each arg
#define OPENAPI_GET_MACRO(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,NAME, ...) NAME 
#define OPENAPI_FOR_EACH(f, ...) \
  OPENAPI_EXPAND(OPENAPI_GET_MACRO(_0,__VA_ARGS__,\
    OPENAPI_CALL_WITH_ARG_10,\
    OPENAPI_CALL_WITH_ARG_9,\
    OPENAPI_CALL_WITH_ARG_8,\
    OPENAPI_CALL_WITH_ARG_7,\
    OPENAPI_CALL_WITH_ARG_6,\
    OPENAPI_CALL_WITH_ARG_5,\
    OPENAPI_CALL_WITH_ARG_4,\
    OPENAPI_CALL_WITH_ARG_3,\
    OPENAPI_CALL_WITH_ARG_2,\
    OPENAPI_CALL_WITH_ARG_1,\
    OPENAPI_CALL_WITH_ARG_0)(f,__VA_ARGS__))

#define OPENAPI_TO_JSON_MEMBER(arg1) \
{ \
    j.AddMember<decltype(this->arg1)>(OPENAPI_LITERAL(arg1), arg1);\
}

#define OPENAPI_FROM_JSON_MEMBER(arg1) \
    if(j.HasKey(OPENAPI_LITERAL(arg1))) \
    { \
        using V = remove_optional<decltype(this->arg1)>::type;\
        this->arg1 = j.GetMember<V>(OPENAPI_LITERAL(arg1)); \
    }

#define OPENAPI_TO_JSON_FUNC(arg1, ...) \
    void arg1::ToJSON(Json & j) const \
    { \
        OPENAPI_FOR_EACH(OPENAPI_TO_JSON_MEMBER, __VA_ARGS__) \
    }

#define OPENAPI_FROM_JSON_FUNC(arg1, ...) \
    void arg1::FromJSON(const Json & j) \
    { \
        OPENAPI_FOR_EACH(OPENAPI_FROM_JSON_MEMBER, __VA_ARGS__) \
    }

#define OPENAP_JSON_CONVERT_FUNCS(arg1, ...) \
    OPENAPI_TO_JSON_FUNC(arg1, __VA_ARGS__) \
    OPENAPI_FROM_JSON_FUNC(arg1, __VA_ARGS__)

#define OPENAPI_JSON_CONVERT_FUNCS_DECLARE \
    void ToJSON(Json & j) const; \
    void FromJSON(const Json & j); 


