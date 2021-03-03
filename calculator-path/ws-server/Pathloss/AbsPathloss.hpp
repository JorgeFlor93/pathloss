#pragma once
#include <vector>
#include "IPathloss.hpp"
#include "../common.h"

class AbsPathloss : public IPathloss{
public:
    virtual ~AbsPathloss(){};
    virtual void calcPathloss(std::vector<antenna> vantenna) override{};
    virtual std::vector<int> setgetDimensions(path corners, std::vector<double> resolution) override{return {};};
    virtual nlohmann::json getParameters(std::vector<antenna> vantennas, std::vector<int> dimensions, ptAtributes atributes) override{return {};};
};