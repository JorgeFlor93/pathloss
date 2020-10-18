#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include <math.h>
#include "common.h"
#include "models/fspl.hh"
#include "models/hata.hh"

double LossReport(struct site source, struct site destination, float freq, std::string pm, std::string pmenv);
double Distance(struct site site1, struct site site2);
double miles_to_km(double miles);
