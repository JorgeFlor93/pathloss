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
    else{
        /* collect */
        //this->pathloss.emplace_back(loss);
    }
}

void Emisor::sendfflush(){
    this->data = this->pathloss;
    nlohmann::json j_out;
    j_out["fflush"] = this->data;
    this->ws->sendPartial(j_out);
}