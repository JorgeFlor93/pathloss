
#include "Atributes.hpp"

void Atributes::setAtributes(nlohmann::json atributes)
{   
    //this->propagationMethod = atributes["propagationMethod"].get<std::string>();
    this->resolution = atributes["resolution"].get<std::string>();
    //this->cacltype = atributes["caclType"][0].get<nlohmann::json>();
    this->progress = atributes["progress"].get<int>();
    std::string pmenv = atributes["propagationMode"].get<std::string>();
    if(pmenv == "URBAN") this->propagationModel = 1;
    else if(pmenv == "SUBURBAN") this->propagationModel = 2;
    else if(pmenv == "RURAL") this->propagationModel = 3; 
 
    for(nlohmann::json& it : atributes["antennas"])
    {
        this->vectorTx.emplace_back(Antenna{
                                    (it)["lat"].get<double>(), 
                                    (it)["lon"].get<double>(), 
                                    (it)["height"].get<float>(),
                                    (it)["type"].get<std::string>(),
                                    (it)["id"].get<std::string>(),
                                    (it)["frequency"].get<float>()
                                });
    }
}