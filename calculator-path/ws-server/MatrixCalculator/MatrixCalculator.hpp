
#pragma once
#include <vector>

class MatrixCalculator {
public:
  std::vector<std::vector<std::vector<double>>> add(std::vector<std::vector<std::vector<double>>> operands);
  double divide(std::vector<std::vector<std::vector<double>>> operands);
  double multiply(std::vector<std::vector<std::vector<double>>> operands);
  double substract(std::vector<std::vector<std::vector<double>>> operands);
};