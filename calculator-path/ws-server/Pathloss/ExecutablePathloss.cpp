
#include "ExecutablePathloss.hpp"

void ExecutablePathloss::addFixedPathloss(){ //crear 

  this->pathloss = SingletonPathloss::getPathloss();
  this->pathloss->lambdaFunction();
}

void ExecutablePathloss::execute() {  //ejecutar

  this->pathloss->calcPathloss();
  
}

nlohmann::json ExecutablePathloss::result(){ //enviar
  nlohmann::json j_out;
  j_out["Partial"] = sresult;
  return j_out;
}




