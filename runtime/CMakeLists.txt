cmake_minimum_required(VERSION 3.14)

set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
    include/*.h
    src/*.cpp
)

add_library(openapi_runtime STATIC 
    ${SOURCES}
)

target_include_directories(
    openapi_runtime
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(OPENAPI_BuildTests)
    add_subdirectory(test)
endif()