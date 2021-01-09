#pragma once
#include <vector>

class IPathloss{
public:
virtual ~IPathloss(){};
virtual std::vector<double> calcPathloss(const double tlat, const double tlon, const float theight, const float frequency) = 0; 
};