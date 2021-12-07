cmake_policy(SET CMP0048 NEW)
project(openapi_runtime VERSION 0.0.1 LANGUAGES CXX)

cmake_minimum_required(VERSION 3.14)

set (CMAKE_CXX_STANDARD 17)

# add dependencies
# install boost on ubuntu :  sudo apt-get install libboost-all-dev
set(OPENAPI_MAIN_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(OPENAPI_MAIN_PROJECT ON)
endif()

if (POLICY CMP0077)
    # Allow CMake 3.13+ to override options when using FetchContent / add_subdirectory.
    cmake_policy(SET CMP0077 NEW)
endif ()

# project build options
option(OPENAPI_BuildTests     "Build the unit tests when BUILD_TESTING is enabled." ${OPENAPI_MAIN_PROJECT})
option(OPENAPI_BuildExamples  "Build examples"                                      ${OPENAPI_MAIN_PROJECT})

# json option
set(OPENAPI_JSON "OPENAPI_NLOHMANNJSON" CACHE STRING "Json provider choosen")
set_property(CACHE OPENAPI_JSON PROPERTY STRINGS "OPENAPI_NLOHMANNJSON" "OPENAPI_RAPIDJSON")

message("Using OPENAPI_JSON = " ${OPENAPI_JSON})
# validate 
get_property(OPT_STRINGS CACHE OPENAPI_JSON PROPERTY STRINGS)
if (NOT OPENAPI_JSON IN_LIST OPT_STRINGS)
  message(FATAL_ERROR "Wrong value of the parameter 'OPENAPI_JSON'")
endif()

if(OPENAPI_BuildTests)
  # import google test
  include(FetchContent)
  FetchContent_Declare(
    googletest
    # Specify the commit you depend on and update it regularly.
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
  )
  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  message(STATUS "Fetching googletest")
  FetchContent_MakeAvailable(googletest)
  enable_testing()
endif(OPENAPI_BuildTests)

add_subdirectory(runtime)
add_subdirectory(client)
add_subdirectory(json)

if(OPENAPI_BuildExamples)
  add_subdirectory(examples)
endif()