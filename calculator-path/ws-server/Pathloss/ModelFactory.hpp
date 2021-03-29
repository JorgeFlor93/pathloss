#pragma once
#include "Model.hpp"
#include "../common.h"

class ModelFactory {
public:
    Model* createModel(pmodel pm , penv pe, int tp, ptAtributes corners);
};