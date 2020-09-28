
#pragma once
#include "../Executor/Executable.hpp"
#include "MatrixCalculator.hpp"
#include <vector>
#include <iostream>

class ExecutableMatrixCalculator: public Executable, public MatrixCalculator {
public:
  ~ExecutableMatrixCalculator(){};
  void setMatrixCalculator(MatrixCalculator matrixcalculator);
  std::vector<std::vector<std::vector<double>>> add(std::vector<std::vector<std::vector<double>>> operands);
  double divide(std::vector<std::vector<std::vector<double>>> operands);
  double multiply(std::vector<std::vector<std::vector<double>>> operands);
  double substract(std::vector<std::vector<std::vector<double>>> operands);
  void execute();
  void addFixedMatrixCalculation(std::string typeoperation, std::vector<std::vector<std::vector<double>>> operands);
  nlohmann::json result();
private:
  MatrixCalculator matrixcalculator;
  std::vector<std::vector<std::vector<double>>> payload;
  std::string operation;
  nlohmann::json sresult;
};