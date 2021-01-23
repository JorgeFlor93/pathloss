#pragma once
#include <iostream>
#include <vector>
#include <string>
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
#include "ModelFactory.hpp"

class ExecutablePathloss: public Executable{
public:
  ExecutablePathloss(ptAtributes atributes, std::vector<antenna> vantenna) : atributes(atributes), vantenna(vantenna){};
  void addFixedPathloss();
  virtual void execute() override final;
  nlohmann::json result();
private:
  ptAtributes atributes;
  std::vector<antenna> vantenna;
  IPathloss* pathloss;
  nlohmann::json res;
};








