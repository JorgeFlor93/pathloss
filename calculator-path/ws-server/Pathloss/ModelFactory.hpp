#pragma once
#include "Model.hpp"
#include "../common.h"
#include "../Communications/HttpGet.hpp"
#include "../Communications/Websocket.hpp"

class ModelFactory {
public:
    Model* createModel(pmodel pm , penv pe, path corners, int n);
};