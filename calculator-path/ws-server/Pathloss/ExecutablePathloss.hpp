#pragma once
#include "../Executor/Executable.hpp"
#include "Pathloss.hpp"
#include <iostream>
#include "../json.hpp"
#include <vector>

class ExecutablePathloss: public Executable, public Pathloss{
public:
  ~ExecutablePathloss(){};
  void setPathloss(Pathloss pathloss); //decorar
  void addFixedPathloss(nlohmann::json atributes, nlohmann::json operands);
  void setAtributes(nlohmann::json atributes);
  void execute(nlohmann::json work);
  nlohmann::json result(nlohmann::json f);
  nlohmann::json setAreaLoss();

private:
  Pathloss pathloss;
  nlohmann::json sresult;
};








