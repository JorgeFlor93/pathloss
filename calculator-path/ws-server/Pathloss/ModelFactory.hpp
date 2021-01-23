#pragma once
#include "Algorithm.hpp"
#include "../common.h"

class ModelFactory {
public:
    Algorithm* createModel(pmodel pm , penv pe);
};