
#include "ExecutableMatrixCalculator.hpp"
/*
vector< vector<int> >::iterator row;
vector<int>::iterator col;
for(...){
    for (row = vvi.begin(); row != vvi.end(); row++) {
        for (col = row->begin(); col != row->end(); col++) {
            // do stuff ...cout << *col << '\n'
        }
    }
}
*/
std::vector<std::vector<std::vector<double>>> MatrixCalculator::add(std::vector<std::vector<std::vector<double>>> operands) {
  std::vector<std::vector<std::vector<double>>> result;
  double acc = 0;
  for (std::vector<std::vector<std::vector<double>>>::iterator z = operands.begin(); z != operands.end(); ++z) {
    for (std::vector<std::vector<double>>::iterator i = z->begin(); i != z->end(); ++i) {
      for (std::vector<double>::iterator j = i->begin(); j != i->end(); ++j) {
        acc += *j;
      }
    }
  } 
  return result;
}

double MatrixCalculator::divide(std::vector<std::vector<std::vector<double>>> operands) {
  double acc = 0;
  double acc2 = 0;
  int c = 0;
  for (std::vector<std::vector<std::vector<double>>>::iterator z = operands.begin(); z != operands.end(); ++z) {
    for (std::vector<std::vector<double>>::iterator i = z->begin(); i != z->end(); ++i) {
      for (std::vector<double>::iterator j = i->begin(); j != i->end(); ++j) {
        if(c < 4) acc += *j;
        if(c >= 4) acc2 += *j;
        c++;
      }
    }
  }
  return acc/acc2;
}

double  MatrixCalculator::multiply(std::vector<std::vector<std::vector<double>>> operands){
  double acc = 0;
  double acc2 = 0;
  int c = 0;
  for (std::vector<std::vector<std::vector<double>>>::iterator z = operands.begin(); z != operands.end(); ++z) {
    for (std::vector<std::vector<double>>::iterator i = z->begin(); i != z->end(); ++i) {
      for (std::vector<double>::iterator j = i->begin(); j != i->end(); ++j) {
        if(c < 4) acc += *j;
        if(c >= 4) acc2 += *j;
        c++;
      }
    }
  }
  return acc*acc2;
}

double  MatrixCalculator::substract(std::vector<std::vector<std::vector<double>>> operands){
  double acc = 0;
  double acc2 = 0;
  int c = 0;
  for (std::vector<std::vector<std::vector<double>>>::iterator z = operands.begin(); z != operands.end(); ++z) {
    for (std::vector<std::vector<double>>::iterator i = z->begin(); i != z->end(); ++i) {
      for (std::vector<double>::iterator j = i->begin(); j != i->end(); ++j) {
        if(c < 4) acc += *j;
        if(c >= 4) acc2 += *j;
        c++;
      }
    }
  }
  return acc-acc2;
}
