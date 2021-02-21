#pragma once   
#include <vector>
#include "../common.h"
#include "../Communications/Websocket.hpp"
#include "../json.hpp"

class Emisor{
public:
    Emisor(Websocket* ws, int progress, std::vector<antenna> vantennas): ws(ws), progress(progress), vantennas(vantennas){
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
    std::vector<antenna> vantennas;
    int cont;
    std::vector<double> pathloss;
    nlohmann::json data;
    int totalpoints;
};