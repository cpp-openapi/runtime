file(GLOB SOURCES
    include/*.h
    src/*.cpp
)

add_library(todo-list-client STATIC "${cxx_strict}" ${SOURCES})
target_include_directories(
    todo-list-client
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../model/include # remove
)
target_link_libraries(
    todo-list-client
    PUBLIC todo-list-model
    PUBLIC cpp-openapi-runtime 
    PUBLIC cpp-openapi-json-nlohmann # choose one json lib
    PUBLIC cpp-openapi-rapidjson
    PUBLIC cpp-openapi-client-beast # choose one client lib
    PUBLIC cpp-openapi-client-curlpp
)