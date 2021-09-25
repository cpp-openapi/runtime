file(GLOB SOURCES
    include/*.h
    src/*.cpp
)

add_library(todo-list STATIC "${cxx_strict}" ${SOURCES})

target_include_directories(
    todo-list
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(todo-list
  PUBLIC cpp-openapi-runtime 
  PUBLIC cpp-openapi-json-nlohmann # choose one json lib
  PUBLIC cpp-openapi-rapidjson
  PUBLIC cpp-openapi-client-beast # choose one client lib
  PUBLIC cpp-openapi-client-curlpp
)

find_package(Boost REQUIRED system thread) # for stacktrace

# example executable
add_executable("main" main.cpp)
target_include_directories(
  main
  PUBLIC ${Boost_INCLUDE_DIR}
)
target_link_libraries("main" PRIVATE ${Boost_LIBRARIES} todo-list cpp-openapi-client-beast   
PUBLIC pthread dl) # for stacktrace