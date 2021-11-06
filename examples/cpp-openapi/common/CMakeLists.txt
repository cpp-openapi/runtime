file(GLOB SOURCES
    include/*.h
    src/*.cpp
)

add_library(todo-list-common STATIC "${cxx_strict}" ${SOURCES})
target_include_directories(
    todo-list-common
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(todo-list-common PUBLIC ${OPENAPI_JSON}=1)

if(OPENAPI_JSON STREQUAL  "OPENAPI_NLOHMANNJSON")
    target_link_libraries(todo-list-common
        PUBLIC cpp-openapi-json-nlohmann
    )
elseif(OPENAPI_JSON STREQUAL  "OPENAPI_RAPIDJSON")
    target_link_libraries(todo-list-common
        PUBLIC cpp-openapi-rapidjson
    )
endif()

target_link_libraries(todo-list-common
    PUBLIC cpp-openapi-json
)