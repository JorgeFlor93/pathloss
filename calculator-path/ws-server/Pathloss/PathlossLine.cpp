#include "PathlossLine.hpp"

void PathlossLine::calcPathloss(std::vector<antenna> vantenna)
{
  
    std::vector<double> fullvector;
    fullvector.emplace_back(this->corners.lat2 - this->corners.lat1);
    fullvector.emplace_back(this->corners.lon2 - this->corners.lon1);
    
    double modul = modulo(fullvector); 

    std::vector<double> unitvector;
    unitvector.emplace_back((fullvector[0] / modul) * this->resolution[0]);
    unitvector.emplace_back((fullvector[1] / modul) * this->resolution[1]);
    
    std::vector<double> currentpoint;
    currentpoint.emplace_back(this->corners.lat1);
    currentpoint.emplace_back(this->corners.lon1);
    
    int end = round((modul)/(resolution[0]));
    this->emisor->reservePathloss(end, 1);
    this->algorithm = this->model->lambdaFunction();
    for(int i=0;i<end;i++){
        for(auto& antenna : vantenna){
        this->emisor->collectLoss(this->algorithm(currentpoint[0], currentpoint[1], 1/* i + (j*amount_lat) */, 
                                    antenna.lat, antenna.lon, antenna.height, antenna.freq));
        currentpoint[0] = currentpoint[0] + unitvector[0];
        currentpoint[1] = currentpoint[1] + unitvector[1];
        }
    }
    this->emisor->sendfflush();
} 

