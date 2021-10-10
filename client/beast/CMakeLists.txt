# add beast deps

# boost has various deps. So prefer system boost install

# boost root needs to be pre set in system env var
# set(BOOST_ROOT "C:\\local\\boost_1_76_0")

set(Boost_USE_STATIC_LIBS ON)
# ADD_DEFINITIONS("-DBOOST_ALL_NO_LIB")
find_package(Boost REQUIRED)

file(GLOB SOURCES
    include/*.h
    src/*.cpp
)

project(cpp-openapi-client-beast)

add_library(cpp-openapi-client-beast STATIC "${cxx_strict}" 
# ${Boost_LIBRARIES} 
${SOURCES})

target_include_directories(
    cpp-openapi-client-beast
    PUBLIC
    ${Boost_INCLUDE_DIR}
    ${cpp-openapi-client-beast_SOURCE_DIR}/include
)

# get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
# foreach(dir ${dirs})
#   message(STATUS "dir='${dir}'")
# endforeach()

target_link_libraries(cpp-openapi-client-beast 
# PRIVATE ${Boost_LIBRARIES} 
PRIVATE cpp-openapi-runtime
)