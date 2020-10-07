#include "ExecutablePathloss.hpp"

std::vector<std::vector<double>> ExecutablePathloss::displayArea(nlohmann::json varea){ //crear
  return this->pathloss.displayArea(varea);
}

std::vector<std::vector<double>> ExecutablePathloss::displayvTx(std::vector<std::vector<double>> vTx){ //crear
  return this->pathloss.displayvTx(vTx);
}

std::vector<std::vector<double>> ExecutablePathloss::setAreaLoss(std::vector<double> tx){
  return this->pathloss.setAreaLoss(tx);
}

std::vector<std::vector<double>> ExecutablePathloss::getAllTxLoss(std::vector<std::vector<double>> vTx, std::vector<double> points){
  return this->pathloss.getAllTxLoss(vTx, points);
}

std::vector<double> ExecutablePathloss::getBestTx(std::vector<double> points){
  return this->pathloss.getBestTx(points);
}

void ExecutablePathloss::setCalculus(float freq, std::string prop_model, std::string env_mode, nlohmann::json areaCoord, std::vector<std::vector<double>> vTx, std::vector<double> points){
  return this->pathloss.setCalculus(freq, prop_model, env_mode, areaCoord, vTx, points);
}

void ExecutablePathloss::addFixedPathloss(nlohmann::json atributes, nlohmann::json operands){ //crear 
  this->model =  atributes["model"].get<std::string>();
  this->env_mode = atributes["propagation_model"].get<std::string>();
  this->jsarea = atributes["areaCorners"][0].get<nlohmann::json>();
  this->vTx = atributes["AntennasTx"][0];
  this->freq = atributes["frequency"].get<float>();
  this->points = operands["Points"].get<std::vector<double>>();
  
  this->setCalculus(this->freq, this->model, this->env_mode, this->jsarea, this->vTx["value"].get<std::vector<std::vector<double>>>(), this->points); // Se establece el área 
}

void ExecutablePathloss::execute(nlohmann::json work) {  //ejecutar
  if(work["id"].get<std::string>() == "A1000"){
    this->sresult = this->getBestTx(this->points);
  }
  else if(work["id"].get<std::string>() == "A2000"){
    this->sresult = this->getAllTxLoss(this->vTx["value"].get<std::vector<std::vector<double>>>(), this->points);
  }
  // else if(*it == "printAreaLoss"){
  //   for(std::vector<std::vector<double>>::iterator itb=this->vTx.begin(); itb != vTx.end();++itb){
  //     this->sresult = this->setAreaLoss(*itb);
  //   }
  // }
  // else if(*it == "HeightPoint"){
  //   Coord p;
  //   p.assignCoord(point.at(0), point.at(1), point.at(2));
  //   this->sresult = p.getTxalt(); 
  // }
  // else if(operation == "displayArea") this->sresult = this->displayArea(this->jsarea);
  // else if(operation == "displayvtx") this->sresult = this->displayvTx(this->vTx);  
}

void ExecutablePathloss::setPathloss(Pathloss pathloss){ //decorar
    this->pathloss = pathloss;
}

nlohmann::json ExecutablePathloss::result(nlohmann::json f){ //enviar
  nlohmann::json j_out;
  j_out[f["function"].get<std::string>()] = this->sresult;
  return j_out;
}




