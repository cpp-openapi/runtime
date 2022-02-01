# this lib is WIP. Do not add to other dependencies

file(GLOB SOURCES
    include/openapi/testutil/*.h
    src/*.cpp
)

add_library(openapi_testutil
    STATIC ${SOURCES}
)

target_include_directories(openapi_testutil
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(openapi_testutil
    PUBLIC openapi_runtime
)