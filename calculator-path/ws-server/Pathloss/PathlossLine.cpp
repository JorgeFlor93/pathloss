#include "PathlossLine.hpp"

std::vector<double> PathlossLine::calcPathloss(std::vector<antenna> vantenna)
{
  
    std::vector<double> fv(this->atributes.corners.lat2 - this->atributes.corners.lat1, this->atributes.corners.lon2 - this->atributes.corners.lon1);
    
    double modul = modulo(fv); 

    std::vector<double> unitvector((fv.front() / modul) * this->atributes.resolution[0], (fv.back() / modul) * this->atributes.resolution[1]);

    std::vector<double> currentpoint(this->atributes.corners.lat1, this->atributes.corners.lon1);

    int end = round((modul)/(atributes.resolution[0]));

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

