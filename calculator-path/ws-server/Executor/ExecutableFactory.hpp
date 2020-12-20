
#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "../json.hpp"
#include "Executable.hpp"
#include "../Pathloss/ExecutablePathloss.hpp"
#include "../common.h"

class ExecutableFactory {
public:
  Executable* create(std::string executable, nlohmann::json njatributes);
};

void setResolution(std::string resolution);