#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "common.h"
// #include "auxFuncts.hh"
// #include "inputs.hh"
#include "models/cost.hh"
#include "models/ecc33.hh"
#include "models/ericsson.hh"
#include "models/fspl.hh"
#include "models/hata.hh"
#include "models/itwom3.0.hh"
#include "models/sui.hh"

double LossReport(struct site source, struct site destination, std::string propmodel, std::string pmenvl, float freq);

double Distance(struct site site1, struct site site2);
double miles_to_km(double miles);
