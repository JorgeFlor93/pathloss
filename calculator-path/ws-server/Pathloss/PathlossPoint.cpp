
#include "PathlossPoint.hpp"

void PathlossPoint::calcPathloss(std::vector<antenna> vantenna)
{
    this->emisor->reservePathloss(vantenna.capacity(), 1);
    this->algorithm = this->model->lambdaFunction();
    for(auto& antenna : vantenna){
        this->emisor->collectLoss(this->algorithm(this->corners.lat1, this->corners.lon1, 1/* i + (j*amount_lat) */, 
                                    antenna.lat, antenna.lon, antenna.height, antenna.freq));  
    }
    this->emisor->sendfflush();
} 

