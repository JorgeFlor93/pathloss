
#include "Antenna.hpp"

Antenna::Antenna(double lat, double lon, float height, std::string type, std::string id, float frequency) : 
                    lat(lat), lon(lon), height(height), type(type), id(id), frequency(frequency) {}

struct site Antenna::getStruct(){
  return this->coord.getStruct();
}

float Antenna::getFrequency(){
    return this->frequency;
}

std::string Antenna::getId(){
    return this->id;
}

std::string Antenna::getType(){
    return this->type;
}

double Antenna::getLat(){
    return this->parameters.lat;
}
double Antenna::getLon(){
    return this->parameters.lon;
}
float Antenna::getHeight(){
    return this->parameters.alt;
}