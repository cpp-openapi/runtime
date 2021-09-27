file(GLOB SOURCES
    include/*.h
    src/*.cpp
)

add_library(todo-list-model STATIC "${cxx_strict}" ${SOURCES})
target_include_directories(
    todo-list-model
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(todo-list-model
    PUBLIC cpp-openapi-json
)