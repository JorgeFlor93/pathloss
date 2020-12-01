#include "ExecutablePathloss.hpp"



void ExecutablePathloss::setAtributes(nlohmann::json atributes){//crear
  //return this->atribute.setAtributes(atributes);
  //FactoryAntenna worker{};
  IPathloss* this->calcpath = createPathloss(atributes["caclType"][0]["type"], atributes["propagationMethod"]); //param1 line area or point; param2 egli, hata, cost...
}

void ExecutablePathloss::addFixedPathloss(nlohmann::json atributes){ //crear 
  this->setAtributes(atributes); // Se establece tipo(area, linea, punto), antenas y atributos.
}

void ExecutablePathloss::execute() {  //ejecutar

  //for (vector antennas )
  this->calcpath->calcPath();
  
  // if(work["id"].get<std::string>() == "A3000"){   
  //   this->sresult = this->setAreaLoss();  
  // }
}

nlohmann::json ExecutablePathloss::result(nlohmann::json f){ //enviar
  nlohmann::json j_out;
  j_out[f["function"].get<std::string>()] = this->sresult;
  return j_out;
}




