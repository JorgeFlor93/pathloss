#pragma once
#include "common.h"
#include <iostream>
#include <string>
#include <vector> 
#include "../json.hpp"
#include "distance.hh"
#include "Antenna.hpp"
#include <memory>
#include <functional>
class Pathloss{
public:
  void setAtributes(nlohmann::json atributes);
  nlohmann::json setAreaLoss();
private:
  float freq;
  std::string type;
  std::string propagationMethod;
  int propagationModel;
  std::string resolution;
  nlohmann::json location;
  int progress;
  std::vector<Antenna> vectorTx;
};



