#pragma once
#include "common.h"
#include "coordinate.hpp"
#include <string>

class Antenna: public Coord{
public:
Antenna(double lat, double lon, float height, std::string type, std::string id, float frequency);
Coord coord;
std::string getType();
std::string getId();
float getFrequency();
struct site getStruct();
double getLat();
double getLon();
float getHeight();
std::vector<double> getVector();

private:
double lat;
double lon;
double height;
std::string type;
std::string id;
float frequency;
struct site parameters;
};