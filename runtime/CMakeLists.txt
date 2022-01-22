file(GLOB SOURCES
    include/*.h
    src/*.cpp
)

add_library(openapi_runtime
    STATIC ${SOURCES}
)

target_include_directories(openapi_runtime
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

message("configure runtime")
if(OPENAPI_UTF16_STRINGS)
    target_compile_definitions(openapi_runtime PUBLIC OPENAPI_UTF16_STRINGS=1)
    message("Using OPENAPI_UTF16_STRINGS = 1")
else()
    message("Using OPENAPI_UTF16_STRINGS =")
endif()

if(OPENAPI_BuildTests)
    add_subdirectory(test)
endif()