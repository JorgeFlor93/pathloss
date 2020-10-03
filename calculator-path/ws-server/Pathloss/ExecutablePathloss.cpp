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

void ExecutablePathloss::addFixedPathloss(float freq, std::string prop_model, std::string env_mode, nlohmann::json areaCoord, std::vector<std::vector<double>> vTx, nlohmann::json actions){ //crear 
  this->model = prop_model;  
  this->env_mode = env_mode;
  this->jsarea = areaCoord;
  this->vTx = vTx;
  this->freq = freq;
  this->operations = actions["operation"].get<std::vector<std::string>>();
  this->points = actions["Points"].get<std::vector<double>>();
}

void ExecutablePathloss::execute(std::string work) {  //ejecutar
  this->setCalculus(this->freq, this->model, this->env_mode, this->jsarea, this->vTx, this->points); // Se establece el área 
  if(work == "BestTx"){
    this->sresult = this->getBestTx(this->points);
  }
  else if(work == "AllTxLoss"){
    this->sresult = this->getAllTxLoss(this->vTx, this->points);
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

nlohmann::json ExecutablePathloss::result(){ //enviar
  nlohmann::json j_out;
  j_out["result"] = this->sresult;
  return j_out;
}




