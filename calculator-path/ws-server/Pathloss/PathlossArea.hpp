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

class PathlossArea : public AbsPathloss{
public:
  PathlossArea(Model* model, Emisor* emisor, std::vector<double> res, path corners) : model(model), emisor(emisor), resolution(res), corners(corners){};
  virtual void calcPathloss(std::vector<antenna> vantenna) override final;
  int getDimensionLng(double line_start_lng, double line_end_lng);
  int getDimensionLat(double line_start_lat, double line_end_lat);
private:
  Model* model;
  Emisor* emisor;
  std::vector<double> resolution;
  path corners;
  std::function<double(const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)> algorithm;
};

