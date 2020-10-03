#pragma once
#include "coordinate.hpp"
#include "lossreport.hpp"
#include <vector>
#include <iostream>

class Pairtxrx{
public:
    void setTx(struct site tx);
    void setRx(struct site rx);
    struct site getstx();
    void assignPar(Coord tx, Coord rx);
    void setLoss(float freq, std::string propmodel, std::string pmenv);
    double getLoss();
    Coord& getTx();
    Coord& getRx();
private:
    std::vector<Coord> vp;
    struct site tx;
    struct site rx;
    double loss;
};