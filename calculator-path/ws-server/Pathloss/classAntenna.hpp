#pragma once
#include "common.h"
#include "coordinate.hpp"
#include <string>

class antenna: public Coord{
    private:
    struct site parameters;
    float frequency;
    std::string type;
    std::string id;

    public:
    ~antenna(){};
    Coord coord;
    std::string getType();
    std::string getId();
    float getFrequency();
    struct site getStruct();
    double getLat();
    double getLon();
    float getHeight();
    std::vector<double> getVector();
    void setParameters(double lat, double lon, float height, std::string type, std::string id, float frequency);
};