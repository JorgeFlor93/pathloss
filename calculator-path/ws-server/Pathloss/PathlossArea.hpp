#pragma once
#include <iostream>
#include <string>
#include <vector> 
#include <functional>
#include <math.h>
#include "AbsPathloss.hpp"
#include "Emisor.hpp"
#include "../common.h"
#include "../Communications/Websocket.hpp"
#include "../json.hpp"

class PathlossArea : public AbsPathloss{
public:
  virtual std::vector<double> calcPathloss(const double tlat, const double tlon, const float theight, const float frequency) override final;
  //std::vector<double> areaPathloss(const double tlat, const double tlon, const float theight, const float frequency); /* Antenna */
  virtual void send(std::vector<double> pathloss);
private:
 
};

int getDimensionLng(double line_start_lng, double line_end_lng);
int getDimensionLat(double line_start_lat, double line_end_lat);


