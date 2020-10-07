#pragma once
#include "common.h"
#include <iostream>
#include "coordinate.hpp"
#include <string>
#include <sstream>
#include <vector> 
#include "../json.hpp"
#include "distance.hh"
#include "txrx.hpp"

class Pathloss{
public:
  std::vector<std::vector<double>> displayArea(nlohmann::json varea);
  nlohmann::json wsHttpR();
  std::vector<std::vector<double>> displayvTx(std::vector<std::vector<double>> vTx);
  void setArea(std::vector<double> tl, std::vector<double> br);
  std::vector<Coord> getArea();
  std::vector<std::vector<double>> getvectorArea();
  void setCalculus(float freq, std::string prop_model, std::string env_mode, nlohmann::json areaCoord, std::vector<std::vector<double>> vTx, std::vector<double> points);
  std::vector<double> getBestTx(std::vector<double> point);
  // std::vector<Pairtxrx> getPtrx();
  std::vector<std::vector<double>> setAreaLoss(std::vector<double> tx);
  std::vector<std::vector<double>> getAllTxLoss(std::vector<std::vector<double>> vtx, std::vector<double> points);
private:
  std::vector<Coord> varea;
  std::string env_mode;
  std::string model;
  float freq;
  std::vector<Coord> vTx;
  // std::vector<Pairtxrx> ptrx;
};

double Distance(struct site site1, struct site site2);
double miles_to_km(double miles);



