#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector> 
#include <functional>
#include <algorithm>
#include "Algorithm.hpp"
#include "AbsPathloss.hpp"
#include "Emisor.hpp"
#include "../common.h"
#include "../Communications/Websocket.hpp"
#include "../json.hpp"

class PathlossLine : public AbsPathloss{
public:
  PathlossLine(Algorithm* m, ptAtributes a) : model(m), atributes(a){};
  virtual void calcPathloss(std::vector<antenna> vantenna) override final;
private:
  Algorithm* model;
  ptAtributes atributes;
  std::vector<double> resolution;
};

/* NORM */
template <typename T> 
T modulo(std::vector<T> const& vec) {
    double d = vec.front() * vec.back();
    return sqrt(d);
}