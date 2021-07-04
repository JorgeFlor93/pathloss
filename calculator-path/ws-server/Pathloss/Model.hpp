#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <math.h>
#include <vector>
#include "PathlossAbs.hpp"
#include "../json.hpp"
#include "../common.h"
#include "../Communications/HttpGet.hpp"

class Model{
public:
    
    using Algorithm = std::function<double(const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)>;
    Model(pmodel pm, int pe, int n, HttpGet* httpget, std::string modelName) : pm(pm), propagationEnvironment(pe), n(n), httpget(httpget), modelName(modelName){}; 
    Model(pmodel pm, int pe, int n, std::string modelName) : pm(pm), propagationEnvironment(pe), n(n), modelName(modelName){}; 
    Model::Algorithm createAlgorithm(HttpGet::OnReady onReady);
    pmodel getModel();
    std::string getModelName();
    double calcDistance(const double tlat, const double tlon, const double lat, const double lon);
private:
    pmodel pm;
    int propagationEnvironment;
    int n;
    HttpGet* httpget;
    std::string modelName;
};
