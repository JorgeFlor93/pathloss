
#pragma once
#include "../common.h"
#include "HttpGet.hpp"

class HttpGetFactory {
public:
    HttpGet* createHttpGet(path corners);
};