file(GLOB SOURCES
    include/*.h
    src/*.cpp
)

add_library(todo_list_common STATIC "${cxx_strict}" ${SOURCES})
target_include_directories(
    todo_list_common
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(todo_list_common PUBLIC ${OPENAPI_JSON}=1)

if(OPENAPI_JSON STREQUAL  "OPENAPI_NLOHMANNJSON")
    target_link_libraries(todo_list_common
        PUBLIC openapi_nlohmann_json
    )
elseif(OPENAPI_JSON STREQUAL  "OPENAPI_RAPIDJSON")
    target_link_libraries(todo_list_common
        PUBLIC openapi_rapidjson
    )
endif()

target_link_libraries(todo_list_common
    PUBLIC openapi_json
)