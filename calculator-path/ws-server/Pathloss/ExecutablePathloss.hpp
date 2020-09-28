#pragma once
#include "../Executor/Executable.hpp"
#include "Pathloss.hpp"
#include <iostream>
#include "../json.hpp"
#include <vector>
#include "coordinate.hpp"


class ExecutablePathloss: public Executable, public Pathloss, public cArea{
public:
  ~ExecutablePathloss(){};
  void setPathloss(Pathloss pathloss); //decorar
  void addFixedPathloss(std::string prop_model, std::string type, nlohmann::json areaCoord);
  void execute();
  std::string displayArea(nlohmann::json varea);
  std::string display(std::string pm);
  nlohmann::json result();
private:
  Pathloss pathloss;
  std::string model;
  std::string type;
  nlohmann::json sresult;
  nlohmann::json jsarea;
};








