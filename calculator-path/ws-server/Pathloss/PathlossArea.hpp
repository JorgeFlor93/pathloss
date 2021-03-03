#pragma once
#include <iostream>
#include <string>
#include <vector> 
#include <functional>
#include <math.h>
#include "AbsPathloss.hpp"
#include "Emisor.hpp"
#include "Model.hpp"
#include "../common.h"
#include "../Communications/Websocket.hpp"
#include "../json.hpp"
#include "ParametersSender.hpp"

class PathlossArea : public AbsPathloss{
public:
  PathlossArea(Model* model, Emisor* emisor, std::vector<double> res, path corners) : model(model), emisor(emisor), resolution(res), corners(corners){};
  virtual void calcPathloss(std::vector<antenna> vantenna) override final;
  virtual std::vector<int> setgetDimensions(path corners, std::vector<double> resolution) override final;
  virtual nlohmann::json getParameters(std::vector<antenna> vantennas, std::vector<int> dimensions, ptAtributes atributes) override final;
private:
  Model* model;
  Emisor* emisor;
  std::vector<double> resolution;
  path corners;
  std::function<double(const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)> algorithm;
  double bestloss;
  std::vector<int> dimensions;
};

