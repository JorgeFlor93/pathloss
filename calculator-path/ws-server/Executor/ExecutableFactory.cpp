
#include "ExecutableFactory.hpp"

Executable* ExecutableFactory::create (std::string executable, nlohmann::json atributes, nlohmann::json actions) {
  if(executable == "pathloss"){
    Pathloss pathloss{};
    ExecutablePathloss* executablePathloss = new ExecutablePathloss{};
    executablePathloss->setPathloss(pathloss);

    float freq = atributes["frequency"].get<float>();
    std::string model = atributes["model"].get<std::string>(); 
    nlohmann::json areaCoord = atributes["areaCorners"][0].get<nlohmann::json>();
    std::vector<std::vector<double>> vTx = atributes["AntennasTx"].get<std::vector<std::vector<double>>>();
    std::string env_mode = atributes["propagation_model"].get<std::string>();
    executablePathloss->addFixedPathloss(freq, model, env_mode, areaCoord, vTx, actions);
    return executablePathloss;
  }
  else {
    return nullptr;
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