
#pragma once
#include <vector>
#include "../json.hpp"
#include "Executable.hpp"
#include "../Calculator/Calculator.hpp"
#include "../Calculator/ExecutableCalculator.hpp"
#include "../MatrixCalculator/MatrixCalculator.hpp"
#include "../MatrixCalculator/ExecutableMatrixCalculator.hpp"
#include "../Pathloss/Pathloss.hpp"
#include "../Pathloss/ExecutablePathloss.hpp"
#include <iostream>
#include <string>

class ExecutableFactory {
public:
  Executable* create(std::string executable, nlohmann::json atributes, nlohmann::json actions);
};