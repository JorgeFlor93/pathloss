#pragma once
#include "common.h"
#include "coordinate.hpp"
#include <string>

class Antenna{
public:
Antenna(double lat, double lon, float height, std::string type, std::string id, float frequency);
Coord coord;
std::string getType();
std::string getId();
float getFrequency();
double getLat();
double getLon();
float getHeight();
std::vector<double> getVector();

private:
double lat;
double lon;
float height;
std::string type;
std::string id;
float frequency;
};