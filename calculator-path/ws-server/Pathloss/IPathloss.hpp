#pragma once
#include <vector>

class IPathloss{
public:
virtual ~IPathloss(){};
virtual std::vector<double> calcPathloss() = 0; 
};