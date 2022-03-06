# middleware has routing tools

file(GLOB SOURCES
    include/openapi/runtime/*.h
    src/*.cpp
)

add_library(openapi_runtime_middleware
    STATIC ${SOURCES}
)

target_include_directories(openapi_runtime_middleware
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(openapi_runtime_middleware
    PUBLIC openapi_runtime
)

if(OPENAPI_BuildTests)
    add_subdirectory(test)
endif()