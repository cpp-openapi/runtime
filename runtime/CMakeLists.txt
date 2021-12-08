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

if(OPENAPI_BuildTests)
    add_subdirectory(test)
endif()