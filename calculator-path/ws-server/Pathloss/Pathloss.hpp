#pragma once
#include "common.h"
#include <iostream>
#include "coordinate.hpp"
#include <string>
#include <sstream>
#include <vector> 
#include "../json.hpp"
#include "distance.hh"
#include "classAntenna.hpp"
#include "lossreport.hpp"

class Pathloss{
public:
  void setArea(std::vector<double> tl, std::vector<double> br);
  std::vector<Coord> getArea();
  std::vector<std::vector<double>> getvectorArea();
  std::vector<antenna> setCalculus(nlohmann::json atributes);
  nlohmann::json setAreaLoss();
  double Loss(antenna tx, Coord rx);
  // std::vector<double> getBestTx(std::vector<double> point);
  // std::vector<std::vector<double>> getAllTxLoss(std::vector<double> points);
private:
  std::vector<Coord> varea;
  std::string env_mode;
  std::string model;
  float freq;
  std::vector<antenna> vTx;
  std::string type;
};



