#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <math.h>
#include <vector>
#include "PathlossAbs.hpp"
#include "../json.hpp"
#include "../common.h"
#include "HttpGet.hpp"

class Model{
public:
    
    using Algorithm = std::function<double(const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)>;
    Model(pmodel pm, int pe, HttpGet* httpget) : pm(pm), propagationEnvironment(pe), httpget(httpget){}; 
    Model(pmodel pm, int pe) : pm(pm), propagationEnvironment(pe){}; 
    Model::Algorithm createAlgorithm(HttpGet::OnReady onReady);
    double calcDistance(const double tlat, const double tlon, const double lat, const double lon);
private:
    pmodel pm;
    int propagationEnvironment;
    HttpGet* httpget;
};
