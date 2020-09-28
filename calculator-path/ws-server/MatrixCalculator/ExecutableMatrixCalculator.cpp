
#include "ExecutableMatrixCalculator.hpp"

std::vector<std::vector<std::vector<double>>> ExecutableMatrixCalculator::add(std::vector<std::vector<std::vector<double>>> operands){
  return this->matrixcalculator.add(operands);
}

double ExecutableMatrixCalculator::divide(std::vector<std::vector<std::vector<double>>> operands){
  return this->matrixcalculator.divide(operands);
}

double ExecutableMatrixCalculator::multiply(std::vector<std::vector<std::vector<double>>> operands){
  return this->matrixcalculator.multiply(operands);
}

double ExecutableMatrixCalculator::substract(std::vector<std::vector<std::vector<double>>> operands){
  return this->matrixcalculator.substract(operands);
}

void ExecutableMatrixCalculator::execute() {  
  if (this->operation == "+") this->sresult = this->add(this->payload);
  else if (this->operation == "/") this->sresult = this->divide(this->payload);
  else if (this->operation == "*") this->sresult = this->multiply(this->payload);
  else if (this->operation == "-") this->sresult = this->substract(this->payload);
}

void ExecutableMatrixCalculator::setMatrixCalculator (MatrixCalculator matrixcalculator) {
  this->matrixcalculator = matrixcalculator;
}

void ExecutableMatrixCalculator::addFixedMatrixCalculation(std::string typeoperation, std::vector<std::vector<std::vector<double>>> operands) { 
  this->operation = typeoperation;  
  this->payload = operands;
}

nlohmann::json ExecutableMatrixCalculator::result(){
  nlohmann::json j_out;
  j_out["result"] = this->sresult;
  return j_out;
}