#pragma once
#include <iostream>
#include <string>
#include <vector> 
#include <functional>
#include "AbsPathloss.hpp"
#include "../common.h"
#include "../Communications/Websocket.hpp"
#include "../json.hpp"

class PathlossArea : public AbsPathloss{
public:
  virtual void calcPathloss() override final;
  virtual void lambdaFunction() override final;
  void areaPathloss(const double top_lat , const double top_lng, const double bot_lat, const double bot_lng, /* Area Corners */
                                const double tlat, const double tlon, const float theight, const float frequency, /* Antenna */
                                std::function<double(const double lat, const double lon, const int pos, const double tlat, const double tlon, 
                                  const float theight, const float frequency)> getLoss, /* std::funct */
                                int progress); /* progress */
  virtual void send(std::vector<double> pathloss);
private:
 
};

int getDimensionLng(const double line_start_lng,const double line_end_lng);
int getDimensionLat(const double line_start_lat, const double line_end_lat);


