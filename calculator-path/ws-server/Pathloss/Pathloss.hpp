#pragma once
#include "common.h"
#include <iostream>
#include "coordinate.hpp"
#include <string>
#include <vector> 
#include "../json.hpp"
#include "distance.hh"
#include "Antenna.hpp"
#include "lossreport.hpp"
#include <memory>

class Pathloss{
public:
  void setAtributes(nlohmann::json atributes);
  nlohmann::json setAreaLoss();
  // std::vector<double> getBestTx(std::vector<double> point);
  // std::vector<std::vector<double>> getAllTxLoss(std::vector<double> points);
private:
  float freq;
  std::string type;
  std::string propagationMethod;
  std::string propagationModel;
  std::string resolution;
  nlohmann::json location;
  int progress;
  std::vector<Antenna> vectorTx;
};



