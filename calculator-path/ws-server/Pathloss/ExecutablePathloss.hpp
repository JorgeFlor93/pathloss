#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "../json.hpp"
#include "../Executor/Executable.hpp"
#include "PathlossAbs.hpp"
#include "PathlossArea.hpp"
#include "PathlossLine.hpp"
#include "../Communications/Websocket.hpp"
#include "PathlossInterface.hpp"
#include "../common.h"
#include "SingletonPathloss.hpp"
#include "ModelFactory.hpp"
#include "../Communications/EmisorFactory.hpp"

class ExecutablePathloss: public Executable{
public:
  ExecutablePathloss(ptAtributes atributes, std::vector<antenna> vantenna, int n) : atributes(atributes), vantenna(vantenna), n(n){};
  void addFixedPathloss(Websocket* ws);
  virtual void execute() override final;
  virtual nlohmann::json result();
private:
  ptAtributes atributes;
  std::vector<antenna> vantenna;
  int n;
  std::vector<std::vector<double>> vlatlon;
  PathlossInterface* pathloss;
  nlohmann::json res;
  std::vector<int> dimensions;
};








