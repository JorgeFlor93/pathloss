#pragma once
#include <vector>
#include "../common.h"

class IPathloss{
public:
virtual ~IPathloss(){};
virtual std::vector<double> calcPathloss(std::vector<antenna> vantenna) = 0; 
};