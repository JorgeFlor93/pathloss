#pragma once
#include "common.h"
#include <iostream>
#include "coordinate.hpp"
#include <string>
#include <vector> 
#include "../json.hpp"
#include "distance.hh"
#include "classAntenna.hpp"
#include "lossreport.hpp"

class Pathloss{
public:
  void setAtributes(nlohmann::json atributes);
  nlohmann::json setAreaLoss();
  // std::vector<double> getBestTx(std::vector<double> point);
  // std::vector<std::vector<double>> getAllTxLoss(std::vector<double> points);
private:
  std::vector<Coord> varea;
  float freq;
  std::string type;
  std::string propagationMethod;
  std::string propagationModel;
  std::string resolution;
  nlohmann::json location;
  std::vector<double> propagation;
  std::vector<antenna> vectorTx;
};



