#pragma once
#include <vector>
#include "PathlossInterface.hpp"
#include "../common.h"

class PathlossAbs : public PathlossInterface{
public:
    virtual ~PathlossAbs(){};
    virtual void calcPathloss(std::vector<antenna>& vantenna) override{};
};