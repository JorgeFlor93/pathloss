
#pragma once
#include "../Executor/Executable.hpp"
#include "Calculator.hpp"
#include <vector>
#include <iostream>

class ExecutableCalculator: public Executable, public Calculator {
public:
  ~ExecutableCalculator(){};
  void setCalculator(Calculator calculator);
  double add(std::vector<double> operands);
  double divide(std::vector<double> operands);
  double multiply(std::vector<double> operands);
  double substract(std::vector<double> operands);
  void execute();
  void addFixedCalculation(std::string typeoperation, std::vector<double> operands);
  nlohmann::json result();
private:
  Calculator calculator;
  std::vector<double> payload;
  std::string operation;
  nlohmann::json sresult;
};