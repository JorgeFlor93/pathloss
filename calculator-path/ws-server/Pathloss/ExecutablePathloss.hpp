#pragma once
#include "../Executor/Executable.hpp"
#include "Pathloss.hpp"
#include <iostream>
#include "../json.hpp"
#include <vector>
#include "../Communications/Websocket.hpp"
#include "PathlossFactory.hpp"
#include "IPathloss.hpp"
#include "Atributes.hpp"

class ExecutablePathloss: public Executable{
public:
  void addFixedPathloss(nlohmann::json atributes);
  void setAtributes(nlohmann::json atributes);
  void execute();
  nlohmann::json result(nlohmann::json f);
private:
  IPathloss* calcpath;
  nlohmann::json sresult;
};








