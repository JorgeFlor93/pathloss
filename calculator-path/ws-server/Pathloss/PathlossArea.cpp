#include "PathlossArea.hpp"

void PathlossArea::calcPathloss(std::vector<antenna> vantenna)
{
    int amount_lat = getDimensionLat(this->corners.lat1, this->corners.lat2);
    int amount_lng = getDimensionLng(this->corners.lon1, this->corners.lon2);
    this->emisor->reservePathloss(amount_lat, amount_lng);

    double start_point_lat = this->corners.lat1 - this->resolution[0]/2;
    double current_point_lat = start_point_lat;
    double current_point_lon = this->corners.lon1 + this->resolution[1]/2;
    double start_point_lon = current_point_lon;
    this->algorithm = this->model->lambdaFunction();
   
    
    for(int i = 0; i < amount_lat; i++){
        for(int j = 0; j < amount_lng; j++){
            double bestloss;
            for(auto& antenna : vantenna){
                /*CALCULO DE LA PERDIDA*/ 
                double loss;
                loss = this->algorithm(current_point_lat, current_point_lon, 1/* i + (j*amount_lat) */, 
                                        antenna.lat, antenna.lon, antenna.height, antenna.freq);
                if(antenna.id == "1") bestloss = loss;
                else if (loss <= bestloss) bestloss = loss; 
            }
            this->emisor->collectLoss(bestloss); 
            current_point_lon += this->resolution[0];
        } 
        current_point_lon = start_point_lon;
        current_point_lat -= this->resolution[1];
    }
    this->emisor->sendfflush();
}

int PathlossArea::getDimensionLng(double line_start_lng, double line_end_lng){
    double inc_lng = abs(line_start_lng - line_end_lng);
    return round(inc_lng/this->resolution[1]);
}

int PathlossArea::getDimensionLat(double line_start_lat, double line_end_lat){
    double inc_lat = abs(line_start_lat - line_end_lat);    
    return round(inc_lat/this->resolution[0]);
}

// int PathlossArea::getTotalpoints(const double tl_lat, const double tl_lon, const double br_lat, const double br_lon){
//     return (getDimensionLat(tl_lat, br_lat) * getDimensionLng(tl_lon, br_lon)); // amount_lat * amount_lng;
// }

// for(auto& antenna : vantenna){
    //     this->emisor->collectLoss(this->model->calcDistance(antenna.lat, antenna.lon, current_point_lat, current_point_lon));
    //     this->emisor->collectLoss(antenna.lat);
    //     this->emisor->collectLoss(antenna.lon);
    //     this->emisor->collectLoss(antenna.height);
    //     this->emisor->collectLoss(antenna.freq);
    // }
    // this->emisor->collectLoss(current_point_lat);
    // this->emisor->collectLoss(current_point_lon);
    // this->emisor->collectLoss(this->resolution[0]);
    // this->emisor->collectLoss(amount_lat);
    // this->emisor->collectLoss(amount_lng);