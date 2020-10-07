#pragma once
#include "../Executor/Executable.hpp"
#include "Pathloss.hpp"
#include <iostream>
#include "../json.hpp"
#include <vector>
#include "coordinate.hpp"


class ExecutablePathloss: public Executable, public Pathloss{
public:
  ~ExecutablePathloss(){};
  void setPathloss(Pathloss pathloss); //decorar
  void addFixedPathloss(nlohmann::json atributes, nlohmann::json operands);
  void setCalculus(float freq, std::string prop_model, std::string env_mode, nlohmann::json areaCoord, std::vector<std::vector<double>> vTx, std::vector<double> points);
  void execute(nlohmann::json work);
  std::vector<std::vector<double>> displayArea(nlohmann::json varea);
  std::vector<std::vector<double>> displayvTx(std::vector<std::vector<double>> vTx);
  nlohmann::json result(nlohmann::json f);
  std::vector<double> getBestTx(std::vector<double> point);
  std::vector<std::vector<double>> setAreaLoss(std::vector<double> tx);
  std::vector<std::vector<double>> getAllTxLoss(std::vector<std::vector<double>> vTx, std::vector<double> points);
private:
  Pathloss pathloss;
  std::string env_mode;
  std::string model;
  float freq;
  nlohmann::json sresult;
  nlohmann::json jsarea;
  nlohmann::json vTx;
  std::vector<std::string> operations;
  std::vector<double> points;
};








