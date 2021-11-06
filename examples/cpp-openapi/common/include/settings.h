#pragma once

#ifdef OPENAPI_RAPIDJSON
#include "openapi_rapidjson.h"
typedef RapidJson Json;
#elif defined(OPENAPI_NLOHMANNJSON)
#include "openapi_nlohmann_json.h"
typedef NlohmannJson Json;
#endif

#include "openapi_json_macro.h"