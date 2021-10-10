add_subdirectory(model)
add_subdirectory(client)

# find_package(Boost REQUIRED system thread) # for stacktrace

# example executable
add_executable("main" main.cpp)
# target_include_directories(
#   main
# #  PUBLIC ${Boost_INCLUDE_DIR}
# )
target_link_libraries("main" PRIVATE todo-list-client
PUBLIC cpp-openapi-runtime # for auth
# PUBLIC pthread dl
# PUBLIC ${Boost_LIBRARIES} # for stacktrace
)