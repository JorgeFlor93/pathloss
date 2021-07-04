#include "PathlossLine.hpp"

void PathlossLine::onReady(std::vector<antenna> vantenna){
    std::vector<double> currentpoint;
    currentpoint.emplace_back(this->corners.lat1);
    currentpoint.emplace_back(this->corners.lon1);
    for(int i=0;i<this->longitudeline[0];i++){
        for(auto& antenna : vantenna){
        this->emisor->collectLoss(this->algorithm(currentpoint[0], currentpoint[1], 1/* i + (j*amount_lat) */, 
                                    antenna.lat, antenna.lon, antenna.height, antenna.freq));
        currentpoint[0] = currentpoint[0] + this->uv[0];
        currentpoint[1] = currentpoint[1] + this->uv[1];
        }
    }
    this->emisor->sendfflush();
    this->emisor->sendAll();
}

void PathlossLine::calcPathloss(std::vector<antenna>& vantenna){
    this->emisor->reservePathloss(this->longitudeline[0], 1);
    this->algorithm = this->model->createAlgorithm([vantenna, this](){this->onReady(vantenna);});
    if(this->model->getModel() == pmodel::fspl || this->model->getModel() == pmodel::soil) {onReady(vantenna);}
}

std::vector<int> PathlossLine::setgetDimensions(path corners, std::vector<double> resolution){
    // longitud de la línea. Variable end
    std::vector<double> fullvector;
    fullvector.emplace_back(this->corners.lat2 - this->corners.lat1);
    fullvector.emplace_back(this->corners.lon2 - this->corners.lon1);
    
    double modul = modulo(fullvector); 

    std::vector<double> unitvector;
    unitvector.emplace_back((fullvector[0] / modul) * this->resolution[0]);
    unitvector.emplace_back((fullvector[1] / modul) * this->resolution[1]);
    this->uv = unitvector;
    int end = round((modul)/(resolution[0]));
    this->longitudeline.emplace_back(end);
    return this->longitudeline;
}

nlohmann::json PathlossLine::getParameters(std::vector<antenna> vantennas, std::vector<int> dimensions, ptAtributes atributes){
    //Crear JSON con los parámetros
    nlohmann::json j_out;
    j_out["parameters"] = {
    {"totalpoints", dimensions[0]},
    {"wlongitude", dimensions[0]},
    {"numantennas", vantennas.size()},
    {"progress", atributes.progress},
    {"corners", {
        {"topleft", {
        {"lat", atributes.corners.lat1},
        {"lon", atributes.corners.lon1}
        }},
        {"botright", {
        {"lat", atributes.corners.lat2},
        {"lon", atributes.corners.lon2}
        }}
    }}
    };
    j_out["type"] = "dimensions";
    return j_out;
}