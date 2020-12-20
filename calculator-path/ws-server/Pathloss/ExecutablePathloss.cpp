
#include "ExecutablePathloss.hpp"

void ExecutablePathloss::addFixedPathloss(){ //crear 
  this->pathloss = SingletonPathloss::getPathloss();
  Algorithm exc;  
  exc.lambdaFunction();
}

void ExecutablePathloss::execute() {  //ejecutar

  this->aux = this->pathloss->calcPathloss();
}

nlohmann::json ExecutablePathloss::result(){ //enviar
  nlohmann::json j_out;
  j_out["Partial"] = this->aux;
  return j_out;
}




