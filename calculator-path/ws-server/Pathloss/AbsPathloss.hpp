#pragma once
#include <vector>
#include "IPathloss.hpp"

class AbsPathloss : public IPathloss{
public:
    virtual void calcPathloss() override;
    virtual void lambdaFunction() override;
    virtual void send(std::vector<double> pathloss) = 0;
};