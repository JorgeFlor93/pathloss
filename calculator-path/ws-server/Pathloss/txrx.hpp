#pragma once
#include "coordinate.hpp"
#include "lossreport.hpp"
#include <vector>
#include <iostream>
#include "classAntenna.hpp"

class Pairtxrx{
public:
    void setTx(antenna tx);
    void setRx(struct site rx);
    struct site getstx();
    // void assignPar(Coord tx, Coord rx);
    void setLoss(float freq, std::string propmodel, std::string pmenv);
    double getLoss();
    antenna getTx();
    Coord& getRx();
private:
    std::vector<Coord> vp;
    antenna tx;
    struct site rx;
    double loss;
};