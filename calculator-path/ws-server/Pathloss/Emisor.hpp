#pragma once   
#include <vector>
#include "../common.h"
#include "../Communications/Websocket.hpp"
#include "../json.hpp"

class Emisor{
public:
    Emisor(Websocket* ws, int progress): ws(ws), progress(progress){}; 
    void collectLoss(double loss);
private:
    Websocket* ws;
    int progress; 
    int cont;
    std::vector<double> pathloss;
    nlohmann::json data;
};