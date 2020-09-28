
#include "Calculator.hpp"

double Calculator::add(std::vector<double> operands){
  double acc = 0;
  for (std::vector<double>::size_type i = 0; i < operands.size(); ++i) {
    acc += operands[i];
  }
  return acc;
}

double Calculator::divide(std::vector<double> operands){
  double acc = operands[0];
  for (std::vector<double>::size_type i = 1; i < operands.size(); ++i) {
    acc /= operands[i];
  }
  return acc;
}

double Calculator::multiply(std::vector<double> operands){
  double acc = 1;
  for (std::vector<double>::size_type i = 0; i < operands.size(); ++i) {
    acc *= operands[i];
  }
  return acc;
}

double Calculator::substract(std::vector<double> operands){
  double acc = operands[0];
  for (std::vector<double>::size_type i = 1; i < operands.size(); ++i) {
    acc -= operands[i];
  }
  return acc;
}
