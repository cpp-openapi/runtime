file(GLOB SOURCES
    include/*.h
    src/*.cpp
)

add_subdirectory(providers)

add_library(openapi_json
    STATIC  ${SOURCES}
)

target_include_directories(openapi_json
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# for shared types
target_link_libraries(openapi_json
    PUBLIC openapi_runtime
)

if(OPENAPI_BuildTests)
    add_subdirectory(test)
endif()