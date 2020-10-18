#pragma once
#include "common.h"
#include <vector>

class Coord{
    public:
    ~Coord(){};
    Coord(){}; // Constructor sin parámetros
    bool assignCoord(double lat, double lon, float txalt);
    bool validCoord(double lat, double lon, float alt);
    double getLat();
    double getdisLon(); //Verdadera Longitude    
    double getLon(); // Longitud para encontrar el DEM del punto
    float setAlt(); // Calcular Altura total 
    float getAlt(); // Obtener Altura_Tx + Altura_DEM
    float getTxalt(); // Altura_Tx
    struct site getStruct();
    private:
    struct site point; // lat, lon, alt , loss , dislon del punto
    double loss;
};