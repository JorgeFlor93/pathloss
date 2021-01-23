#pragma once
#include <vector>
#include "IPathloss.hpp"
#include "../common.h"

class AbsPathloss : public IPathloss{
public:
    virtual ~AbsPathloss(){};
    virtual std::vector<double> calcPathloss(std::vector<antenna> vantenna) override{
        return {};
    }
    virtual void send(std::vector<double> pathloss) = 0;
};