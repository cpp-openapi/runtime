message(STATUS "Fetching rapidjson")
include(FetchContent)
FetchContent_Declare(RapidJSON
  GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
  GIT_TAG 00dbcf2c6e03c47d6c399338b6de060c71356464
)
set(RAPIDJSON_BUILD_DOC off CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_EXAMPLES off CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_TESTS off CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_THIRDPARTY_GTEST off CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(RapidJSON)


file(GLOB SOURCES
    include/*.h
    src/*.cpp
)

project(cpp-openapi-rapidjson)

add_library(cpp-openapi-rapidjson STATIC "${cxx_strict}" 
${SOURCES})

target_include_directories(
  cpp-openapi-rapidjson
  PUBLIC ${cpp-openapi-rapidjson_SOURCE_DIR}/include
  PUBLIC ${RapidJSON_SOURCE_DIR}/include
)

target_link_libraries(cpp-openapi-rapidjson PUBLIC cpp-openapi-json)
# target_link_libraries(cpp-openapi-rapidjson INTERFACE RapidJSON)