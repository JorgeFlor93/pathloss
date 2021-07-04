
#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "../json.hpp"
#include "Executable.hpp"
#include "../Pathloss/ExecutablePathloss.hpp"
#include "../common.h"
#include "../Communications/Websocket.hpp"

class ExecutableFactory{
public:
  ExecutableFactory(int n): n(n){};
  void create(std::string executable, nlohmann::json njatributes, Websocket* ws, std::function<void(Executable*)> onReady);
  std::vector<double> setResolution(std::string resolution); 
private:
int n;
  std::vector<antenna> vectorantennas;
  ptAtributes atributes;
  HttpGet* httpget;
};

