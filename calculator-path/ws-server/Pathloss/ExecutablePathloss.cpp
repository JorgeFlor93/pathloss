
#include "ExecutablePathloss.hpp"

void ExecutablePathloss::addFixedPathloss(){ //crear 
  this->pathloss = SingletonPathloss::getPathloss();
  Algorithm exc;  
  exc.lambdaFunction();
}

void ExecutablePathloss::execute() {  //ejecutar

  this->res = this->pathloss->calcPathloss(vAntennas.front().lat, vAntennas.front().lon, vAntennas.front().height, vAntennas.front().freq);
}

nlohmann::json ExecutablePathloss::result(){ //enviar
  nlohmann::json j_out;
  j_out["Partial"] = this->res;
  return j_out;
}




