#include "Emisor.hpp"


void Emisor::reservePathloss(int amount_lat, int amount_lng){
    this->pathloss.reserve(sizeof(double) * amount_lat * amount_lng);
}

void Emisor::collectLoss(double loss){
    /* collect */
    this->pathloss.emplace_back(loss);
    ++(this->cont);
    if(this->cont == this->progress){
        /* send */
        this->data = this->pathloss;
        nlohmann::json j_out;
        j_out["Partial"] = this->data;
        this->ws->sendPartial(j_out);
        this->cont = 0;
        this->pathloss.clear();
    }   
}

void Emisor::bestLoss(double loss){
    nlohmann::json d;
    d = loss;
    nlohmann::json j_out;
    j_out["Best Loss"] = d;
    this->ws->sendPartial(j_out);
}

void Emisor::bestAntenna(antenna a){
    nlohmann::json d = {
        {"id", a.id},
        {"frequency", a.freq},
        {"latitude", a.lat},
        {"longitude", a.lon},
        {"height", a.height}
    };
    nlohmann::json j_out;
    j_out["Best Antenna"] = d;
    this->ws->sendPartial(j_out);
}

void Emisor::sendfflush(){
    this->data = this->pathloss;
    nlohmann::json j_out;
    j_out["fflush"] = this->data;
    this->ws->sendPartial(j_out);
}