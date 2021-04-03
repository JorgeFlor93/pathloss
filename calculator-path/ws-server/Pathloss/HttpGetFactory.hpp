
#pragma once
#include "../common.h"
#include "HttpGet.hpp"
#include "../Communications/Websocket.hpp"

class HttpGetFactory {
public:
    HttpGet* createHttpGet(path corners, Websocket* ws);
};