#pragma once   
#include <vector>
#include "../common.h"
#include "../Communications/Websocket.hpp"
#include "../json.hpp"

class Emisor{
public:
    Emisor(Websocket* ws, int progress, std::vector<antenna> vantennas, path corners): ws(ws), progress(progress), vantennas(vantennas), corners(corners), cont(0), pathloss(), data(), totalpoints(){}; 
    void collectLoss(double loss);
    void sendAll();
    void reservePathloss(int amount_lat, int amount_lng);
    void bestLoss(double loss);
    void bestAntenna(antenna a);
    void sendfflush();
    void antennafflush(std::string id);
private:
    Websocket* ws;
    int progress; 
    std::vector<antenna> vantennas;
    path corners;
    int cont;
    std::vector<double> pathloss;
    nlohmann::json data;
    int totalpoints;
};