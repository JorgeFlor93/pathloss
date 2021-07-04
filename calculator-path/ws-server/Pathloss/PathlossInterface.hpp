#pragma once
#include <vector>
#include "../common.h"

class PathlossInterface{
public:
virtual ~PathlossInterface(){};
virtual void calcPathloss(std::vector<antenna>& vantenna) = 0; 
virtual std::vector<int> setgetDimensions(path corners, std::vector<double> resolution) = 0;
virtual nlohmann::json getParameters(std::vector<antenna> vantennas, std::vector<int> dimensions, ptAtributes atributes) = 0;
};