
#include "ExecutableFactory.hpp"

Executable* ExecutableFactory::create(std::string executable, nlohmann::json njatributes) {

  if(executable == "pathloss"){
    /* Asigno atributos */
    atributes.propagationModel = njatributes["propagationModel"].get<std::string>();
    atributes.calcType = njatributes["caclType"][0].get<nlohmann::json>();
    atributes.type = njatributes["caclType"][0]["type"].get<std::string>();
    atributes.progress = njatributes["progress"].get<int>();
    std::string pmenv = njatributes["propagationEnvironment"].get<std::string>();
    if(pmenv == "URBAN") atributes.propagationEnv = 1;
    else if(pmenv == "SUBURBAN") atributes.propagationEnv = 2;
    else if(pmenv == "RURAL") atributes.propagationEnv = 3; 
    atributes.resolution = njatributes["resolution"].get<std::string>();
    setResolution(atributes.resolution);

    antenna typeAnt;
    for(nlohmann::json& it : njatributes["antennas"])
    {
        typeAnt.lat = it["lat"].get<double>(); 
        typeAnt.lon = it["lon"].get<double>();
        typeAnt.height = it["height"].get<float>();
        typeAnt.type = it["type"].get<std::string>();
        typeAnt.id = it["id"].get<std::string>();
        typeAnt.freq = it["frequency"].get<float>();
        vAntennas.emplace_back(typeAnt);
        // vAntennas.emplace_back(typeAnt_t{
        //                             (it)["lat"].get<double>(), 
        //                             (it)["lon"].get<double>(), 
        //                             (it)["height"].get<float>(),
        //                             (it)["type"].get<std::string>(),
        //                             (it)["id"].get<std::string>(),
        //                             (it)["frequency"].get<float>()
        //                         });
    }

    ExecutablePathloss* executablePathloss = new ExecutablePathloss{}; //decorador
    executablePathloss->addFixedPathloss(); 
    return executablePathloss;
  }
  else {
    return nullptr;
  }
}

void setResolution(std::string resolution){

/* Resolution (point-to-point distance) 
* 0.00208333333 -> 225m
* 0.0002777778 -> 30m (1 arcsec)
* 0.000458333 -> 50m
* 0.000808333 -> 90m (3 arcsec)
*/
    if(resolution == "90m"){
        lat_res = 0.000808333;
        lng_res = 0.000808333;
    }
    else if(resolution == "30m"){
        lat_res = 0.0002777778;
        lng_res = 0.0002777778;
    }
}

/*
for (nlohmann::json::iterator action = this->actions["actions"].begin(); action != this->actions["actions"].end(); ++action) {
    std::string operation = (*action)["operation"].get<std::string>();
    double out = executable->execute(operation); //Se llama a execute

std::string s = j.dump();    // {"happy":true,"pi":3.141}

// serialization with pretty printing
// pass in the amount of spaces to indent
std::cout << j.dump(4) << std::endl;
    
*/