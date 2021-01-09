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