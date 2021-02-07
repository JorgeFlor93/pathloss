#pragma once   
#include <vector>
#include "../common.h"
#include "../Communications/Websocket.hpp"
#include "../json.hpp"

class Emisor{
public:
    Emisor(Websocket* ws, int progress): ws(ws), progress(progress){
        cont = 0;
    }; 
    void collectLoss(double loss);
    void reservePathloss(int amount_lat, int amount_lng);
    void bestLoss(double loss);
    void bestAntenna(antenna a);
    void sendfflush();
    void antennafflush(std::string id);
private:
    Websocket* ws;
    int progress; 
    int cont;
    std::vector<double> pathloss;
    nlohmann::json data;
    int totalpoints;
};