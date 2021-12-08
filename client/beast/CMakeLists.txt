# add beast deps

# boost has various deps. So prefer system boost install

# boost root needs to be pre set in system env var
# set(BOOST_ROOT "C:\\local\\boost_1_76_0")

set(Boost_USE_STATIC_LIBS ON)

# we use header only
ADD_DEFINITIONS("-DBOOST_ALL_NO_LIB")
find_package(Boost REQUIRED)

file(GLOB SOURCES
    include/*.h
    src/*.cpp
)

add_library(openapi_client_beast STATIC "${cxx_strict}" 
# ${Boost_LIBRARIES} 
${SOURCES})

target_include_directories(
    openapi_client_beast
    PUBLIC
    ${Boost_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
# foreach(dir ${dirs})
#   message(STATUS "dir='${dir}'")
# endforeach()

target_link_libraries(openapi_client_beast 
# PRIVATE ${Boost_LIBRARIES} 
    PRIVATE openapi_runtime
)