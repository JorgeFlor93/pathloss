
#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "../json.hpp"
#include "Executable.hpp"
#include "../Pathloss/ExecutablePathloss.hpp"
#include "../common.h"

class ExecutableFactory{
public:
  Executable* create(std::string executable, nlohmann::json njatributes);
  std::vector<double> setResolution(std::string resolution); 
private:
  std::vector<antenna> vectorantennas;
  ptAtributes atributes;
};

