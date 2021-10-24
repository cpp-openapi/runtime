
file(GLOB SOURCES
    *_test.cpp
)

set(OPENAPI_JSON "OPENAPI_NLOHMANNJSON" CACHE STRING "Json provider choosen")
set_property(CACHE OPENAPI_JSON PROPERTY STRINGS "OPENAPI_NLOHMANNJSON" "OPENAPI_RAPIDJSON")

message("Using OPENAPI_JSON = " ${OPENAPI_JSON})
# validate 
get_property(OPT_STRINGS CACHE OPENAPI_JSON PROPERTY STRINGS)
if (NOT OPENAPI_JSON IN_LIST OPT_STRINGS)
  message(FATAL_ERROR "Wrong value of the parameter 'OPENAPI_JSON'")
endif()

# strip file extension
#message("sources are  " ${SOURCES})
foreach(test_file ${SOURCES})
    #message("test file is " ${test_file} "bindir " ${CMAKE_BINARY_DIR})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    
    # set json provider
    target_compile_definitions(${test_name} PRIVATE ${OPENAPI_JSON}=1)
    
    target_link_libraries(${test_name} PRIVATE gtest_main cpp-openapi-json cpp-openapi-json-nlohmann cpp-openapi-rapidjson)
    add_test(NAME ${test_name} COMMAND ${test_name} WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endforeach()