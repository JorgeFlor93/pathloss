#pragma once
#include "AbsPathloss.hpp"
#include "models/fspl.hh"
#include "models/hata.hh"
#include "models/egli.hh"
#include "../json.hpp"
#include "../common.h"

class Algorithm{
public:
    void lambdaFunction();
};

double calcDistance(const double tlat, const double tlon, const double lat, const double lon);
double calcHata(const double lat,const double lon, const float height, const double tlat, const double tlon, const float theight, const float frequency, const int tipo_terreno);
double calcFSPL(const double lat,const double lon, const double tlat, const double tlon, const float theight, const float frequency);
double calcEgli(const double lat,const double lon, const float height, const double tlat, const double tlon, const float theight, const float frequency);
int getTotalpoints(const double tl_lat, const double tl_lon, const double br_lat, const double br_lon);