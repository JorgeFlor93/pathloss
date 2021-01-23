
#include "ExecutablePathloss.hpp"

void ExecutablePathloss::addFixedPathloss(){ //crear 
  ModelFactory modelfactory;
  this->pathloss = SingletonPathloss::getPathloss(modelfactory.createModel(this->atributes.propagationmodel, this->atributes.propagationEnvironment), this->atributes);
}

void ExecutablePathloss::execute() {  //ejecutar
  if(this->pathloss == nullptr){
    this->res = "Objeto a nullptr";
  }
  else{
    this->res = this->pathloss->calcPathloss(this->vantenna);
  }
}

nlohmann::json ExecutablePathloss::result(){ //enviar
  nlohmann::json j_out;
  j_out["Partial"] = this->res;
  return j_out;
}




 