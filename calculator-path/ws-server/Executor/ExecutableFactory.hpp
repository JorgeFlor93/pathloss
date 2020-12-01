
#pragma once
#include <vector>
#include "../json.hpp"
#include "Executable.hpp"
#include "../Pathloss/ExecutablePathloss.hpp"
#include <iostream>
#include <string>

class ExecutableFactory {
public:
  Executable* create(std::string executable, nlohmann::json atributes);
};
