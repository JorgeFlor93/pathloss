
#include <iostream>
#include "txrx.hpp"

void Pairtxrx::setTx(struct site tx){
    this->tx = tx;
}
void Pairtxrx::setRx(struct site rx){
    this->rx = rx;
}

struct site Pairtxrx::getstx(){
    return this->tx;
}
void Pairtxrx::assignPar(Coord tx, Coord rx){
    this->vp.push_back(tx);
    this->vp.push_back(rx);
}

Coord& Pairtxrx::getTx(){
    return this->vp.front();
}

Coord& Pairtxrx::getRx(){
    return this->vp.back();
}

void Pairtxrx::setLoss(int propmodel, int pmenv){
    this->loss = LossReport(this->tx, this->rx, propmodel, pmenv);
}

double Pairtxrx::getLoss(){
    return this->loss;
}
