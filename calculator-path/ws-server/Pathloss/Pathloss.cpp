#include "Pathloss.hpp"

void Pathloss::setAtributes(nlohmann::json atributes)
{   
    this->propagationMethod = atributes["propagationMethod"].get<std::string>();
    this->resolution = atributes["resolution"].get<std::string>();
    this->location = atributes["location"][0].get<nlohmann::json>();
    this->progress = atributes["progress"].get<int>();
    std::string pmenv = atributes["propagation_mode"].get<std::string>();
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

nlohmann::json Pathloss::setAreaLoss(){
    std::vector<double> propagation;
    nlohmann::json jout;
    Distance d;
    d.set_res(this->resolution); // Input Resolution (30m, 90m)
    double tl_lat = this->location["topleft"][0]["lat"].get<double>();
    double tl_lon = this->location["topleft"][0]["lon"].get<double>();
    double br_lat = this->location["botright"][0]["lat"].get<double>();
    double br_lon = this->location["botright"][0]["lon"].get<double>();
    int area_points = 0;
    area_points = d.getTotalpoints(tl_lat, tl_lon, br_lat, br_lon); // TotalPoints
    int tipo_terreno = this->propagationModel;
    float height = 100;
    std::function<double(const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)> accion;
    if(this->propagationMethod == "hata")
    {
        accion = [&tipo_terreno, &height](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
        {
            return calcHata(lat, lon, height, tlat, tlon, theight, frequency, tipo_terreno);
        };
    }
    else if(this->propagationMethod == "fspl")
    {
        accion = [](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
        {
            return calcFSPL(lat, lon, tlat, tlon, theight, frequency);
        };  
    }  
    for(Antenna& itx : this->vectorTx){ 
        propagation = d.get_arealoss(tl_lat, tl_lon, br_lat, br_lon, itx.getLat(), itx.getLon(), itx.getHeight(), itx.getFrequency(), accion);          
        jout.emplace_back(nlohmann::json::array({"antenna", {
                        {"id", itx.getId()}, 
                        {"type", itx.getType()},
                        {"lat", itx.getLat()},
                        {"lon", itx.getLon()},
                        {"height", itx.getHeight()},
                        {"frequency", itx.getFrequency()},
                        {"Area points", area_points},
                        {"Area Loss", propagation}}
                    }));     
    }
    return jout;
}


