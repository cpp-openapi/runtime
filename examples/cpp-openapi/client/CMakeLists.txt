file(GLOB SOURCES
    include/*.h
    src/*.cpp
)

add_library(todo_list_client
    STATIC ${SOURCES}
)

target_include_directories(
    todo_list_client
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    todo_list_client
    PUBLIC todo_list_model
    PUBLIC openapi_runtime
)

target_compile_definitions(todo_list_common PUBLIC ${OPENAPI_CLIENT}=1)

if(OPENAPI_CLIENT STREQUAL  "OPENAPI_CLIENT_CURLPP")
    target_link_libraries(todo_list_client
        PRIVATE openapi_client_curlpp
    )
elseif(OPENAPI_CLIENT STREQUAL  "OPENAPI_CLIENT_BREAST")
    target_link_libraries(todo_list_client
        PRIVATE openapi_client_beast
    )
    if(NOT WIN32) # asio and std::thread needs pthread
        target_link_libraries(todo_list_client
            PRIVATE pthread
        )
    endif()
endif()