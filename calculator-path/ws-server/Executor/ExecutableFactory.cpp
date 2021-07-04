
#include "ExecutableFactory.hpp"
#include "../Communications/HttpGetAntenna.hpp"
#include "../Communications/HttpGet.hpp"
#include <iostream>

void ExecutableFactory::create(std::string executable, nlohmann::json njatributes, Websocket* ws, std::function<void(Executable*)> onReady) {

  if(executable == "pathloss"){
    std::cout << this->n <<": Parsing parameters" << std::endl; 
    /* 
    *   Leer JSON y 
    *   Asignar atributos
    */
    
    /* Model */
    bool aux = true;
    if(njatributes["propagationModel"].get<std::string>() == "fspl") {
      this->atributes.propagationmodel = pmodel::fspl; 
      aux = false;
    }
    else if(njatributes["propagationModel"].get<std::string>() == "sui") this->atributes.propagationmodel = pmodel::sui;
    else if(njatributes["propagationModel"].get<std::string>() == "soil") {
      this->atributes.propagationmodel = pmodel::soil;
      aux = false;    
    }
    else if(njatributes["propagationModel"].get<std::string>() == "ecc33") this->atributes.propagationmodel = pmodel::ecc33;
    else if(njatributes["propagationModel"].get<std::string>() == "itwom") this->atributes.propagationmodel = pmodel::itwom;
    else if(njatributes["propagationModel"].get<std::string>() == "ericcson") this->atributes.propagationmodel = pmodel::ericcson;
    else if(njatributes["propagationModel"].get<std::string>() == "hata") this->atributes.propagationmodel = pmodel::hata;
    else if(njatributes["propagationModel"].get<std::string>() == "cost") this->atributes.propagationmodel = pmodel::cost;
    else if(njatributes["propagationModel"].get<std::string>() == "egli") this->atributes.propagationmodel = pmodel::egli;
    else if(njatributes["propagationModel"].get<std::string>() == "pel") this->atributes.propagationmodel = pmodel::pel;
    
    /* progress */
    this->atributes.progress = njatributes["progress"].get<int>();

    /* Corners */ 
    this->atributes.edges = njatributes["corners"][0].get<nlohmann::json>();
    if(njatributes["type"].get<std::string>() == "area") {
      this->atributes.enumtype = ptype::Area;
      atributes.corners.lat1 = atributes.edges["topleft"][0]["lat"].get<double>();
      atributes.corners.lon1 = atributes.edges["topleft"][0]["lon"].get<double>();
      atributes.corners.lat2 = atributes.edges["botright"][0]["lat"].get<double>();
      atributes.corners.lon2 = atributes.edges["botright"][0]["lon"].get<double>();
    }
    else if(njatributes["type"].get<std::string>() == "line"){
      this->atributes.enumtype = ptype::Line;
      atributes.corners.lat1 = atributes.edges["startpoint"][0]["lat"].get<double>();
      atributes.corners.lon1 = atributes.edges["startpoint"][0]["lon"].get<double>();
      atributes.corners.lat2 = atributes.edges["endpoint"][0]["lat"].get<double>();
      atributes.corners.lon2 = atributes.edges["endpoint"][0]["lon"].get<double>();
    }
    else if(njatributes["type"].get<std::string>() == "point"){
      this->atributes.enumtype = ptype::Point;
      atributes.corners.lat1 = atributes.edges["point"][0]["lat"].get<double>();
      atributes.corners.lon1 = atributes.edges["point"][0]["lon"].get<double>();
      atributes.corners.lat2 = 0;
      atributes.corners.lon2 = 0;
    }
    
    /* Environment */
    if(njatributes["propagationEnvironment"].get<std::string>() == "urban") this->atributes.propagationEnvironment = penv::urban;
    else if(njatributes["propagationEnvironment"].get<std::string>() == "suburban") this->atributes.propagationEnvironment = penv::suburban;
    else if(njatributes["propagationEnvironment"].get<std::string>() == "rural") this->atributes.propagationEnvironment = penv::rural; 

    /* Resolution */
    this->atributes.resolution = setResolution(njatributes["resolution"].get<std::string>());

    /* Antennas */
    std::vector<std::vector<double>> vlatlon;
    for(nlohmann::json& it : njatributes["antennas"]){
      antenna a;
      a.id = it["id"].get<std::string>();
      a.lat = it["lat"].get<double>(); 
      a.lon = it["lon"].get<double>();
      a.height = it["height"].get<float>();
      a.freq = it["frequency"].get<float>();

      std::vector<double> geoAntennaloc;
      geoAntennaloc.emplace_back(a.lat);
      geoAntennaloc.emplace_back(a.lon);
      vlatlon.emplace_back(geoAntennaloc);

      this->vectorantennas.emplace_back(a);
    }
      if(!aux){
        ExecutablePathloss* executablePathloss = new ExecutablePathloss{this->atributes, this->vectorantennas, this->n}; //decorador
        executablePathloss->addFixedPathloss(ws); 
        onReady(executablePathloss);
      }
      else{
        /* Get Tx Heights */
        HttpGetAntenna httpGetAntenna{vlatlon, this->n};
        httpGetAntenna.request([this, &onReady, &ws, &httpGetAntenna](){
          const std::vector<float> antheights = httpGetAntenna.get();
          int c = 0;
          for(auto& antenna : this->vectorantennas){
            antenna.height += antheights[c++];
            // std::cout << antenna.height << std::endl;
          }
          /* Decorator */
          ExecutablePathloss* executablePathloss = new ExecutablePathloss{this->atributes, this->vectorantennas, this->n}; //decorador
          executablePathloss->addFixedPathloss(ws); 
          onReady(executablePathloss);
        });
      }
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
  if(resolution == "90m"){ // 3 arc sec
    rv.emplace_back(0.000808333);
    rv.emplace_back(0.000808333);
    return rv;
  }
  else if(resolution == "30m"){ // 1 arc sec
    rv.emplace_back(0.0002777778);
    rv.emplace_back(0.0002777778);
    return rv;
  }
  else if(resolution == "250m"){  
    rv.emplace_back(0.00208333333);
    rv.emplace_back(0.00208333333);
    return rv;
  }
  else{
    return{};
  }
}
