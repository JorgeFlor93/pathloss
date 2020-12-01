#pragma once
#include "common.h"
#include <string>

class Antenna{
public:
Antenna(double lat, double lon, float height, std::string type, std::string id, float frequency);
virtual void calcPathloss() override;
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