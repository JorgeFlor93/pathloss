
#include "ExecutableFactory.hpp"

Executable* ExecutableFactory::create(std::string executable, nlohmann::json njatributes) {

  if(executable == "pathloss"){
    /* Asigno atributos */
    //this->atributes.propagationModel = njatributes["propagationModel"].get<std::string>();
    if(njatributes["propagationModel"].get<std::string>() == "fspl") this->atributes.propagationmodel = pmodel::fspl; 
    else if(njatributes["propagationModel"].get<std::string>() == "hata") this->atributes.propagationmodel = pmodel::hata;
    else if(njatributes["propagationModel"].get<std::string>() == "egli") this->atributes.propagationmodel = pmodel::egli;
    
    this->atributes.progress = njatributes["progress"].get<int>();
    this->atributes.edges = njatributes["corners"][0].get<nlohmann::json>();

    if(njatributes["type"].get<std::string>() == "area") this->atributes.enumtype = ptype::Area;
    else if(njatributes["type"].get<std::string>() == "line") this->atributes.enumtype = ptype::Line;
    else if(njatributes["type"].get<std::string>() == "point") this->atributes.enumtype = ptype::Point;
    
    if(njatributes["propagationEnvironment"].get<std::string>() == "urban") this->atributes.propagationEnvironment = penv::urban;
    else if(njatributes["propagationEnvironment"].get<std::string>() == "suburban") this->atributes.propagationEnvironment = penv::suburban;
    else if(njatributes["propagationEnvironment"].get<std::string>() == "rural") this->atributes.propagationEnvironment = penv::rural; 

    this->atributes.resolution = setResolution(njatributes["resolution"].get<std::string>());

    for(nlohmann::json& it : njatributes["antennas"]){
      antenna a;
      a.id = it["id"].get<std::string>();
      a.lat = it["lat"].get<double>(); 
      a.lon = it["lon"].get<double>();
      a.height = it["height"].get<float>();
      a.freq = it["frequency"].get<float>();
      this->vectorantennas.emplace_back(a);
    }

    ExecutablePathloss* executablePathloss = new ExecutablePathloss{this->atributes, this->vectorantennas}; //decorador
    executablePathloss->addFixedPathloss(); 
    return executablePathloss;
  }
  else {
    return nullptr;
  }
}

std::vector<double> ExecutableFactory::setResolution(std::string resolution){

/* Resolution
* 0.00208333333 -> 225m
* 0.0002777778 -> 30m (1 arcsec)
* 0.000458333 -> 50m
* 0.000808333 -> 90m (3 arcsec)
*/  

  std::vector<double> rv;
  if(resolution == "90m"){
    rv.emplace_back(0.000808333);
    rv.emplace_back(0.000808333);
    return rv;
  }
  else if(resolution == "30m"){
    rv.emplace_back(0.0002777778);
    rv.emplace_back(0.0002777778);
    return rv;
  }
  else{
    return{};
  }
}
