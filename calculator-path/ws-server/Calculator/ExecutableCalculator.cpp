
#include "ExecutableCalculator.hpp"

double ExecutableCalculator::add(std::vector<double> operands){
  return this->calculator.add(operands);
}

double ExecutableCalculator::divide(std::vector<double> operands){
  return this->calculator.divide(operands);
}

double ExecutableCalculator::multiply(std::vector<double> operands){
  return this->calculator.multiply(operands);
}

double ExecutableCalculator::substract(std::vector<double> operands){
  return this->calculator.substract(operands);
}

void ExecutableCalculator::execute() {  
  if (this->operation == "+") this->sresult = this->add(this->payload);
  else if (this->operation == "/") this->sresult = this->divide(this->payload);
  else if (this->operation == "*") this->sresult = this->multiply(this->payload);
  else if (this->operation == "-") this->sresult = this->substract(this->payload);
}

void ExecutableCalculator::setCalculator(Calculator calculator) {
  this->calculator = calculator;
}

void ExecutableCalculator::addFixedCalculation(std::string typeoperation, std::vector<double> operands) { 
  this->operation = typeoperation;  
  this->payload = operands;
}

nlohmann::json ExecutableCalculator::result(){
  nlohmann::json j_out;
  j_out["result"] = this->sresult;
  return j_out;
}