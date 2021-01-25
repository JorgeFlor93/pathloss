#pragma once
#include <iostream>
#include <string>
#include <vector> 
#include <functional>
#include <math.h>
#include "Model.hpp"
#include "AbsPathloss.hpp"
#include "Emisor.hpp"
#include "../common.h"
#include "../Communications/Websocket.hpp"
#include "../json.hpp"

class PathlossLine : public AbsPathloss{
public:
  PathlossLine(Model* m, Emisor* e, std::vector<double> r, path c) : model(m), emisor(e), resolution(r), corners(c){};
  virtual void calcPathloss(std::vector<antenna> antenna) override final;
private:
  Model* model;
  Emisor* emisor;
  std::vector<double> resolution;
  path corners;
  std::function<double(const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)> algorithm;
};

/* NORM para vector de 2 componentes*/
template <typename T> 
T modulo(std::vector<T> const& vec) {
    double d = vec[0] * vec[0] + vec[1] * vec[1];
    return sqrt(d);
}