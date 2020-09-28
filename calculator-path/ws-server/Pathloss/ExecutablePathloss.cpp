#include "ExecutablePathloss.hpp"

std::string ExecutablePathloss::display(std::string pm){ //crear
    return this->pathloss.display(pm);
}

std::string ExecutablePathloss::displayArea(nlohmann::json varea){ //crear
    return this->pathloss.display(varea);
}

void ExecutablePathloss::addFixedPathloss(std::string prop_model, std::string type, nlohmann::json areaCoord){ //crear 
  this->model = prop_model;  
  this->type = type;
  this->jsarea = areaCoord;
}

void ExecutablePathloss::execute() {  //ejecutar
  //this->sresult = this->display(this->model);
  this->sresult = this->displayArea(this->jsarea);
}

void ExecutablePathloss::setPathloss(Pathloss pathloss){ //decorar
    this->pathloss = pathloss;
}

nlohmann::json ExecutablePathloss::result(){ //enviar
  nlohmann::json j_out;
  j_out["result"] = this->sresult;
  return j_out;
}




