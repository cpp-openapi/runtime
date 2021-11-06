#pragma once

#ifdef OPENAPI_RAPIDJSON
#include "openapi_rapidjson2.h"
typedef RapidJson2 Json;
#elif defined(OPENAPI_NLOHMANNJSON)
#include "openapi_nlohmann_json2.h"
typedef NlohmannJson2 Json;
#endif

#include "openapi_json_macro.h"