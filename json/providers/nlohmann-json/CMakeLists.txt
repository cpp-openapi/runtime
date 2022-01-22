# json dependency
message(STATUS "Fetching nlohmann json")
include(FetchContent)
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.10.4)
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
# json dep end

file(GLOB SOURCES
    include/openapi/json/*.h
    src/*.cpp
)

add_library(openapi_nlohmann_json
  STATIC ${SOURCES})

target_include_directories(
  openapi_nlohmann_json
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(openapi_nlohmann_json
  PUBLIC openapi_json
  PUBLIC nlohmann_json::nlohmann_json
)