#pragma once

#include "request.h"
#include <functional>
#include <memory>

typedef std::function<void(std::shared_ptr<IOASClientRequest>)> AuthInfoWriter;

AuthInfoWriter APIAuth(std::string key, std::string val);