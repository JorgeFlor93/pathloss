
#include "classAntenna.hpp"

void antenna::setParameters(double lat, double lon, float height, std::string type, std::string id, float frequency){
    this->parameters.lat = lat;
    this->parameters.lon = lon;
    this->parameters.alt = height;
    this->type = type;
    this->id = id;
    this->frequency = frequency;
}

struct site antenna::getStruct(){
  return this->coord.getStruct();
}

float antenna::getFrequency(){
    return this->frequency;
}

std::string antenna::getId(){
    return this->id;
}

std::string antenna::getType(){
    return this->type;
}

double antenna::getLat(){
    return this->parameters.lat;
}
double antenna::getLon(){
    return this->parameters.lon;
}
float antenna::getHeight(){
    return this->parameters.alt;
}