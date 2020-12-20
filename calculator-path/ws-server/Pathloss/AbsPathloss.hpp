#pragma once
#include <vector>
#include "IPathloss.hpp"

class AbsPathloss : public IPathloss{
public:
    virtual ~AbsPathloss(){};
    virtual void send(std::vector<double> pathloss) = 0;
};