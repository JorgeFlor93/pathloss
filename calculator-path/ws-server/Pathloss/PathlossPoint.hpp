#pragma once
#include <iostream>
#include <string>
#include <vector> 
#include <functional>
#include <math.h>
#include "Model.hpp"
#include "PathlossAbs.hpp"
#include "Emisor.hpp"
#include "../common.h"
#include "../Communications/Websocket.hpp"
#include "../json.hpp"

class PathlossPoint : public PathlossAbs{
public:
  PathlossPoint(Model* m, Emisor* e, std::vector<double> r, path c) : model(m), emisor(e), resolution(r), corners(c){};
  virtual void calcPathloss(std::vector<antenna> antenna) override final;
  virtual std::vector<int> setgetDimensions(path corners, std::vector<double> resolution) override final;
  nlohmann::json getParameters(std::vector<antenna> vantennas, std::vector<int> dimensions, ptAtributes atributes) override final;
private:
  Model* model;
  Emisor* emisor;
  std::vector<double> resolution;
  path corners;
  std::function<double(const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)> algorithm;
};