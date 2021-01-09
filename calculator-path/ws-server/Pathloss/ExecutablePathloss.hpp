#pragma once
#include <iostream>
#include <vector>
#include "../json.hpp"
#include "../Executor/Executable.hpp"
#include "AbsPathloss.hpp"
#include "PathlossArea.hpp"
#include "PathlossLine.hpp"
#include "Algorithm.hpp"
#include "../Communications/Websocket.hpp"
#include "IPathloss.hpp"
#include "../common.h"
#include "SingletonPathloss.hpp"

class ExecutablePathloss: public Executable{
public:
  void addFixedPathloss();
  virtual void execute() override final;
  nlohmann::json result();
private:
  IPathloss* pathloss;
  nlohmann::json res;
  std::vector<double> loss;
};








