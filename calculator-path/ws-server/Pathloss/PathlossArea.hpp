#pragma once
#include "common.h"
#include <iostream>
#include <string>
#include <vector> 
#include "../json.hpp"
#include "Antenna.hpp"
#include <memory>
#include <functional>
#include "../Communications/Websocket.hpp"

class PathlossArea{
public:
  void calcPathloss() override;
  nlohmann::json setAreaLoss();
  std::vector<double> getArealoss(const double top_lat , const double top_lng, const double bot_lat, const double bot_lng, /* Area Corners */
                                const double tlat, const double tlon, const float theight, const float frequency, /* Antenna */
                                std::function<double(const double lat, const double lon, const int pos, const double tlat, const double tlon, /* std::funct */
                                const float theight, const float frequency)> getLoss, /* std::funct */
                                int progress); /* progress */
  void setRes(std::string resolution);
  int getTotalpoints(const double tl_lat, const double tl_lon, const double br_lat, const double br_lon);
};

/* Clase Algoritmo */
int getDimensionLng(const double line_start_lng,const double line_end_lng);
int getDimensionLat(const double line_start_lat, const double line_end_lat);
double calcDistance(const double tlat, const double tlon, const double lat, const double lon);

double calcHata(const double lat,const double lon, const float height, const double tlat, const double tlon, const float theight, const float frequency, const int tipo_terreno);
double calcFSPL(const double lat,const double lon, const double tlat, const double tlon, const float theight, const float frequency);
double calcEgli(const double lat,const double lon, const float height, const double tlat, const double tlon, const float theight, const float frequency);

