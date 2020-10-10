
#include "txrx.hpp"

void Pairtxrx::setTx(antenna tx){
    this->tx = tx;
}
void Pairtxrx::setRx(struct site rx){
    this->rx = rx;
}

struct site Pairtxrx::getstx(){
    return this->tx;
}
// void Pairtxrx::assignPar(Coord tx, Coord rx){
//     this->vp.push_back(tx);
//     this->vp.push_back(rx);
// }

antenna Pairtxrx::getTx(){
    return this->tx;
}

Coord& Pairtxrx::getRx(){
    return this->vp.back();
}

void Pairtxrx::setLoss(float freq, std::string propmodel, std::string pmenv){
    this->loss = LossReport(this->tx, this->rx, propmodel, pmenv, freq);
}

double Pairtxrx::getLoss(){
    return this->loss;
}
