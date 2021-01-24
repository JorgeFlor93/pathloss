#pragma once
#include <vector>
#include "../common.h"

class IPathloss{
public:
virtual ~IPathloss(){};
virtual void calcPathloss(std::vector<antenna> vantenna) = 0; 
};