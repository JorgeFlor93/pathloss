#pragma once
#include <iostream>
#include "coordinate.hpp"
#include <string.h>
#include <sstream> 
#include "area.hpp"
#include "../json.hpp"

class Pathloss{
public:
  std::string display(std::string model);
  std::string displayArea(nlohmann::json varea);
};

std::vector<Coord> setArea(std::vector<double> tl, std::vector<double> br);




