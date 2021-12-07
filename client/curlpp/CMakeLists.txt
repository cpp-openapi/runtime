# For more deps on cmake see: https://github.com/dmikushin/binance-cxx-api/blob/master/CMakeLists.txt
# install curl and ssl 
# sudo apt-get install libssl-dev libcurl4-openssl-dev
message(STATUS "Fetching curl")
include(FetchContent)
FetchContent_Declare(CURL 
    GIT_REPOSITORY https://github.com/curl/curl.git
    GIT_TAG c7aef0a945f9b6fb6d3f91716a21dfe2f4ea635f # 7.79.1
)

# Turn off curl options that is not needed
set(BUILD_CURL_EXE off CACHE BOOL "" FORCE)
set(CMAKE_USE_OPENSSL off CACHE BOOL "" FORCE)
set(CMAKE_USE_LIBSSH2 off CACHE BOOL "" FORCE)
set(CMAKE_USE_LIBSSH  off CACHE BOOL "" FORCE)
set(CURL_CA_PATH "none" CACHE STRING "" FORCE)
set(BUILD_TESTING off CACHE BOOL "" FORCE)
# use static curl lib
set(BUILD_SHARED_LIBS off CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(CURL)

# Populate vars for cmake find CURL module
set(CURL_INCLUDE_DIR ${CURL_SOURCE_DIR}/include)
set(CURL_LIBRARY libcurl)

message(STATUS "Fetching curlpp")
include(FetchContent)
FetchContent_Declare(
    curlpp 
    GIT_REPOSITORY https://github.com/jpbarrette/curlpp.git
    GIT_TAG a67c73dde2c5d50b3dd3f898b8c185c23de827f3 # latest
)
set(CURLPP_BUILD_SHARED_LIBS off CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(curlpp)

file(GLOB SOURCES
    include/*.h
    src/*.cpp
)

add_library(openapi_client_curlpp STATIC "${cxx_strict}" 
${SOURCES})

target_include_directories(
    openapi_client_curlpp
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    "${curlpp_SOURCE_DIR}/include"
)

target_link_libraries(openapi_client_curlpp PRIVATE openapi_runtime curlpp_static)