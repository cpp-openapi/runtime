#choose json provider

# nlohmann json is always needed for tests
if(NOT OPENAPI_JSON STREQUAL "OPENAPI_NLOHMANNJSON")
    if(OPENAPI_BuildTests)
        add_subdirectory(nlohmann-json)
    endif()
endif()

if(OPENAPI_JSON STREQUAL  "OPENAPI_NLOHMANNJSON")
    add_subdirectory(nlohmann-json) # test uses this lib, sub dir will be added in test project.
elseif(OPENAPI_JSON STREQUAL  "OPENAPI_RAPIDJSON")
    add_subdirectory(rapidjson)
endif()
