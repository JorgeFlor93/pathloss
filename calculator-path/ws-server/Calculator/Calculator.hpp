
#pragma once
#include <vector>

class Calculator {
public:
  double add(std::vector<double> operands);
  double divide(std::vector<double> operands);
  double multiply(std::vector<double> operands);
  double substract(std::vector<double> operands);
};