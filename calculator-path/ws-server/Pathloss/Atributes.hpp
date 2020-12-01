#pragma once
#include "Antenna.hpp"
#include <vector>
#include <string>
#include "../json.hpp"

class Atributes{
public:
    void setAtributes(nlohmann::json atributes);
private:
    float freq;
    std::string type;
    std::string propagationMethod;
    int propagationModel;
    std::string resolution;
    nlohmann::json cacltype;
    int progress;
    std::vector<Antenna> vectorTx;
};