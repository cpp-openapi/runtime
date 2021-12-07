file(GLOB SOURCES
    include/*.h
    src/*.cpp
)

add_library(todo_list_client STATIC "${cxx_strict}" ${SOURCES})

target_include_directories(
    todo_list_client
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../model/include # remove
)

target_link_libraries(
    todo_list_client
    PUBLIC todo_list_model
    PUBLIC openapi_runtime 
    PUBLIC openapi_client_beast # choose one client lib
    PUBLIC openapi_client_curlpp
)

if(OPENAPI_JSON STREQUAL  "OPENAPI_NLOHMANNJSON")
    target_link_libraries(todo_list_client PRIVATE openapi_nlohmann_json)
elseif(OPENAPI_JSON STREQUAL  "OPENAPI_RAPIDJSON")
    target_link_libraries(todo_list_client PRIVATE openapi_rapidjson)
endif()