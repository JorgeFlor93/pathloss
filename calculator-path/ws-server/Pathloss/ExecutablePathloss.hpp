#pragma once
#include "../Executor/Executable.hpp"
#include "Pathloss.hpp"
#include <iostream>
#include "../json.hpp"
#include <vector>
#include "coordinate.hpp"
#include "classAntenna.hpp"

class ExecutablePathloss: public Executable, public Pathloss{
public:
  ~ExecutablePathloss(){};
  void setPathloss(Pathloss pathloss); //decorar
  void addFixedPathloss(nlohmann::json atributes, nlohmann::json operands);
  std::vector<antenna> setCalculus(nlohmann::json atributes);
  void execute(nlohmann::json work);
  nlohmann::json result(nlohmann::json f);
  nlohmann::json setAreaLoss();
  // std::vector<double> getBestTx(std::vector<double> point);
  // std::vector<std::vector<double>> getAllTxLoss(std::vector<double> points);
private:
  Pathloss pathloss;
  std::vector<antenna> vAntennas;
  std::vector<double> points;
  nlohmann::json sresult;
};








