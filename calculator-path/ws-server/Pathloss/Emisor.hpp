#pragma once   
#include <vector>
#include "../common.h"
#include "../Communications/Websocket.hpp"
#include "../json.hpp"

class Emisor{
public:
    Emisor(Websocket* ws, int progress): ws(ws), progress(progress){}; 
    void collectLoss(double loss);
    void reservePathloss(int amount_lat, int amount_lng);
    void bestLoss(double loss);
    void bestAntenna(antenna a);
    void sendfflush();
private:
    Websocket* ws;
    int progress; 
    int cont;
    std::vector<double> pathloss;
    nlohmann::json data;
};