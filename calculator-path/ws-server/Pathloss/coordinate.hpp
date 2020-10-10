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
    float setAlt(); // Calcular Altura total 
    float getAlt(); // Obtener Altura_Tx + Altura_DEM
    float getTxalt(); // Altura_Tx
    struct site getStruct();
    void setRedalt(float alt); //set alt(alt+elevation) to input point
    // bool setTx(double minloss, struct site tx); //EStablece la Tx mas optima y la guarda en ->btx
    double getBtxloss();//obtiene best Tx Loss
    struct site getBtx();//obtiene estructura btx
    bool assignTx(double minloss, struct site tx);
    
    private:
    struct site point; // lat, lon, alt , loss , dislon del punto
    double loss;
    struct site btx;
};