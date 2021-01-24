#pragma once
#include <vector>
#include "IPathloss.hpp"
#include "../common.h"

class AbsPathloss : public IPathloss{
public:
    virtual ~AbsPathloss(){};
    virtual void calcPathloss(std::vector<antenna> vantenna) override{}
};