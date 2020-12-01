#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "common.h"
#include "Pathloss.hpp"
#include "models/fspl.hh"
#include "models/hata.hh"
#include "models/egli.hh"
#include <math.h>
#include "../Communications/Websocket.hpp"
#include "../json.hpp"

class Area{
public:
std::vector<double> getArealoss(const double top_lat , const double top_lng, const double bot_lat, const double bot_lng, /* Area Corners */
                                const double tlat, const double tlon, const float theight, const float frequency, /* Antenna */
                                std::function<double(const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)> getLoss, 
                                int progress);
void setRes(std::string resolution);
int getTotalpoints(const double tl_lat, const double tl_lon, const double br_lat, const double br_lon);
};

int getDimensionLng(const double line_start_lng,const double line_end_lng);
int getDimensionLat(const double line_start_lat, const double line_end_lat);
double calcDistance(const double tlat, const double tlon, const double lat, const double lon);

double calcHata(const double lat,const double lon, const float height, const double tlat, const double tlon, const float theight, const float frequency, const int tipo_terreno);
double calcFSPL(const double lat,const double lon, const double tlat, const double tlon, const float theight, const float frequency);
double calcEgli(const double lat,const double lon, const float height, const double tlat, const double tlon, const float theight, const float frequency);



// std::vector<double> get_line(double line_start_lat , double line_start_lng, double line_end_lat, double line_end_lng);