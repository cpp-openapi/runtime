
file(GLOB SOURCES
    *_test.cpp
)

# strip file extension
#message("sources are  " ${SOURCES})
foreach(test_file ${SOURCES})
    #message("test file is " ${test_file} "bindir " ${CMAKE_BINARY_DIR})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    
    # set json provider
    target_compile_definitions(${test_name} PRIVATE ${OPENAPI_JSON}=1)
    
    target_link_libraries(${test_name} PRIVATE gtest_main cpp-openapi-json cpp-openapi-json-nlohmann cpp-openapi-rapidjson cpp-openapi-runtime)
    add_test(NAME ${test_name} COMMAND ${test_name} WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endforeach()