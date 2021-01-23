#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <math.h>
#include <vector>
#include "AbsPathloss.hpp"
#include "models/fspl.hh"
#include "models/hata.hh"
#include "models/egli.hh"
#include "../json.hpp"
#include "../common.h"

class Algorithm{
public:
    Algorithm(pmodel pm, int pe) : pm(pm), propagationEnvironment(pe){}; 
    void lambdaFunction();
    double calcDistance(const double tlat, const double tlon, const double lat, const double lon);
    std::function<double(const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)> getAlg();
private:
    pmodel pm ;
    int propagationEnvironment;
    std::function<double(const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)> algorithm;
};
