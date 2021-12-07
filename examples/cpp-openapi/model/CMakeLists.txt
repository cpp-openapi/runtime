file(GLOB SOURCES
    include/*.h
    src/*.cpp
)

add_library(todo_list_model STATIC "${cxx_strict}" ${SOURCES})
target_include_directories(
    todo_list_model
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(todo_list_model
    PUBLIC openapi_json
)

target_link_libraries(todo_list_model
    PUBLIC todo_list_common
)