#include "Emisor.hpp"
#include <iostream>

void Emisor::reservePathloss(int amount_lat, int amount_lng){
    this->totalpoints = amount_lat * amount_lng;
    this->pathloss.reserve(sizeof(double) * amount_lat * amount_lng);
}

void Emisor::collectLoss(double loss){
    /* collect */
    this->pathloss.emplace_back(loss);
    ++(this->cont);
    if(this->cont == (this->progress * this->totalpoints)/100){
        this->cont = 0;
        /* send */
        this->data["result"] = this->pathloss;
        this->data["Progress"] = this->progress;
        this->ws->sendPartial(this->data);
        this->pathloss.clear();
    }   
}

void Emisor::sendfflush(){
    // std::cout << this->n << ":sendfflush" << std::endl;
    this->data = this->pathloss;
    nlohmann::json j_out;
    j_out["result"] = this->data;
    j_out["Progress"] = "fflush";
    this->ws->sendPartial(j_out);
}

void Emisor::sendAll(){
    this->ws->sendFinal();
}


/* Para depurar */

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

void Emisor::antennafflush(std::string id){
    this->data = this->pathloss;
    nlohmann::json j_out;
    j_out["fflush"] = this->data;
    // j_out["Antenna"] = {{"id", id}, {"freq", 10}};
    this->ws->sendPartial(j_out);
    this->pathloss.clear();
    this->cont = 0;
}
