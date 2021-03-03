
#include "ExecutablePathloss.hpp"

void ExecutablePathloss::addFixedPathloss(Websocket* ws){ //crear 
  ModelFactory modelfactory;
  EmisorFactory emisorfactory;
  this->pathloss = SingletonPathloss::getPathloss(modelfactory.createModel(this->atributes.propagationmodel, this->atributes.propagationEnvironment), 
                                                    emisorfactory.createEmisor(ws, this->atributes.progress, this->vantenna, this->atributes.corners), 
                                                      this->atributes.resolution, this->atributes.corners, this->atributes.enumtype);
}

void ExecutablePathloss::execute() {  //ejecutar
  if(this->pathloss == nullptr){
    this->res = "Objeto a nullptr";
  }
  else{
    this->dimensions = this->pathloss->setgetDimensions(this->atributes.corners, this->atributes.resolution);
    this->pathloss->calcPathloss(this->vantenna); //Calcular Pathloss
  }
}

nlohmann::json ExecutablePathloss::result(){ //enviar
  // sendParameters
  return this->pathloss->getParameters(this->vantenna, this->dimensions, this->atributes);
}




