cmake_minimum_required(VERSION 3.14)

set (CMAKE_CXX_STANDARD 17)

# set the project name
project(todo-list)

# add dependencies
# install boost on ubuntu :  sudo apt-get install libboost-all-dev

find_package(Boost REQUIRED system thread)

add_subdirectory(runtime)

add_subdirectory(client)

add_subdirectory(json)

file(GLOB SOURCES
    include/*.h
    src/*.cpp
)

add_library(todo-list "${cxx_strict}" ${SOURCES})

target_include_directories(
    todo-list
    PUBLIC ${todo-list_SOURCE_DIR}/include
)

target_link_libraries(todo-list
  PUBLIC cpp-openapi-runtime 
  PUBLIC cpp-openapi-json-nlohmann # choose one json lib
  PUBLIC cpp-openapi-rapidjson
  PUBLIC cpp-openapi-client-beast # choose one client lib
  PUBLIC cpp-openapi-client-curlpp
)

add_executable("main" main.cpp)
target_include_directories(
  main
  PUBLIC ${Boost_INCLUDE_DIR}
)
target_link_libraries("main" PRIVATE ${Boost_LIBRARIES} todo-list cpp-openapi-client-beast   
PUBLIC pthread dl) # for stacktrace

# tests

# import google test
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(json/test)
add_subdirectory(json/providers/nlohmann-json/test)