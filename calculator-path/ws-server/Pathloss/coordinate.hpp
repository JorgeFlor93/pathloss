#pragma once
#include "common.h"
#include <vector>

class Coord{
    public:
    Coord(){}; // Constructor sin parámetros
    bool assignCoord(double lat, double lon, float txalt);
    bool validCoord(double lat, double lon, float alt);
    std::vector<double> getPos();
    double getLat();
    double getdisLon(); //Verdadera Longitude    
    double getLon(); // Longitud para encontrar el DEM del punto
    float setAlt(); 
    float getAlt(); // Altura_Tx + Altura_DEM
    float getTxalt(); // Altura_Tx
    struct site getStruct();
    void setRedalt(float alt); 
    bool setTx(double minloss, struct site tx);
    double getBtxloss();
    struct site getBtx();
    private:
    struct site point; // lat, lon, alt , loss , dislon del punto
    double loss;
    struct site btx;
};