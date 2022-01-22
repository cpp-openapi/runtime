#pragma once

#ifdef OPENAPI_RAPIDJSON
#include "openapi/json/rapid.h"
typedef RapidJson Json;
#elif defined(OPENAPI_NLOHMANNJSON)
#include "openapi/json/nlohmann.h"
typedef NlohmannJson Json;
#endif

#include "openapi/json/macro.h"