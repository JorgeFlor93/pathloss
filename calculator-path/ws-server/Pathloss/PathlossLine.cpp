#include "PathlossLine.hpp"

/* std::vector<double> PathlossLine::calcPathloss(){
    std::vector<double> loss;
    for(antenna& it : vAntennas){
         loss = linePathloss(it.lat, it.lon, it.height, it.freq);
         break;
    }
    return loss;
} */

std::vector<double> PathlossLine::calcPathloss(const double tlat, const double tlon, const float theight, const float frequency)
{
  
    std::vector<double> fv(corner.lat2 - corner.lat1, corner.lon2 - corner.lon1);
    
    double modul = modulo(fv); 

    std::vector<double> unitvector((fv.front() / modul) * lat_res, (fv.back() / modul) * lng_res);

    std::vector<double> currentpoint(corner.lat1, corner.lon1);

    int end = round((modul)/(lat_res));

    std::vector<double> point_list;
    point_list = currentpoint;

    std::vector<double> pathloss;
    pathloss.reserve(sizeof(double)*end);
    double loss = 0;
    for(int i=0;i<end;i++){
        loss = currentpoint[0] + currentpoint[1] + i; // fake loss
        pathloss.emplace_back(loss);
        // double a = currentpoint.front() + unitvector.front();
        // double b = currentpoint.back() + unitvector.back();
        currentpoint[0] = currentpoint.front() + unitvector.front();
        currentpoint[1] = currentpoint.back() + unitvector.back();;
    }
    return pathloss;
} 

void PathlossLine::send(std::vector<double> loss){}
