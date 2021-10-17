file(GLOB SOURCES
    include/*.h
    src/*.cpp
)

project(cpp-openapi-json)

add_library(cpp-openapi-json STATIC "${cxx_strict}"
${SOURCES})

target_include_directories(
    cpp-openapi-json
    PUBLIC ${cpp-openapi-json_SOURCE_DIR}/include
)

# for shared types
target_link_libraries(cpp-openapi-json PUBLIC cpp-openapi-runtime)

add_subdirectory(providers)

# tests are added in top dir