#include "ExecutablePathloss.hpp"

nlohmann::json ExecutablePathloss::setAreaLoss(){
  return this->pathloss.setAreaLoss();
}

void ExecutablePathloss::setAtributes(nlohmann::json atributes){
  return this->pathloss.setAtributes(atributes);
}

void ExecutablePathloss::addFixedPathloss(nlohmann::json atributes, nlohmann::json operands){ //crear 
  this->setAtributes(atributes); // Se establece location, antenas y atributos.
  // this->points = operands["Points"].get<std::vector<double>>();
}

void ExecutablePathloss::execute(nlohmann::json work) {  //ejecutar
  if(work["id"].get<std::string>() == "A3000"){   
    this->sresult = this->setAreaLoss();  
  }
  // if(work["id"].get<std::string>() == "A1000"){
  //   this->sresult = this->getBestTx(this->points);
  // }
  // else if(work["id"].get<std::string>() == "A2000"){
  //   this->sresult = this->getAllTxLoss(this->points);
  // }
}

void ExecutablePathloss::setPathloss(Pathloss pathloss){ //decorar
    this->pathloss = pathloss;
}

nlohmann::json ExecutablePathloss::result(nlohmann::json f){ //enviar
  nlohmann::json j_out;
  j_out[f["function"].get<std::string>()] = this->sresult;
  return j_out;
}


// std::vector<std::vector<double>> ExecutablePathloss::getAllTxLoss(std::vector<std::vector<double>> vTx, std::vector<double> points){
//   return this->pathloss.getAllTxLoss(vTx, points);
// }

// std::vector<double> ExecutablePathloss::getBestTx(std::vector<double> points){
//   return this->pathloss.getBestTx(points);
// }



