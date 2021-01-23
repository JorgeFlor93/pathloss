#pragma once
#include <iostream>
#include <string>
#include <vector> 
#include <functional>
#include <math.h>
#include "AbsPathloss.hpp"
#include "Emisor.hpp"
#include "Algorithm.hpp"
#include "../common.h"
#include "../Communications/Websocket.hpp"
#include "../json.hpp"

class PathlossArea : public AbsPathloss{
public:
  PathlossArea(Algorithm* model, ptAtributes atributes) : model(model), atributes(atributes){};
  virtual std::vector<double> calcPathloss(std::vector<antenna> vantenna) override final;
  virtual void send(std::vector<double> pathloss);
  int getDimensionLng(double line_start_lng, double line_end_lng);
  int getDimensionLat(double line_start_lat, double line_end_lat);
private:
  Algorithm* model;
  ptAtributes atributes;
  std::function<double(const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)> algorithm;
};



