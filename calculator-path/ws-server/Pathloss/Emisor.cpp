#include "Emisor.hpp"

void Emisor::collectLoss(double loss){
    ++(this->cont);
    if(this->cont == this->progress){
        /* send */
        this->cont = 0;
        this->data = this->pathloss;
        this->pathloss.clear();
        nlohmann::json j_out;
        j_out["Partial"] = this->data;
        this->ws->sendPartial(j_out);
    }   
    else{
        /* collect */
        this->pathloss.emplace_back(loss);
    }
}