if(OPENAPI_CLIENT STREQUAL  "OPENAPI_CLIENT_CURLPP")
    add_subdirectory(curlpp)
elseif(OPENAPI_CLIENT STREQUAL  "OPENAPI_CLIENT_BREAST")
    add_subdirectory(beast)
endif()
