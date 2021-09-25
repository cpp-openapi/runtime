cmake_minimum_required(VERSION 3.14)

set (CMAKE_CXX_STANDARD 17)

# set the project name
project(todo-list)

# add dependencies
# install boost on ubuntu :  sudo apt-get install libboost-all-dev

add_subdirectory(runtime)

add_subdirectory(client)

add_subdirectory(json)

add_subdirectory(examples)

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