#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector> 
#include <functional>
#include <algorithm>
#include "AbsPathloss.hpp"
#include "Emisor.hpp"
#include "../common.h"
#include "../Communications/Websocket.hpp"
#include "../json.hpp"

class PathlossLine : public AbsPathloss{
public:
  virtual std::vector<double> calcPathloss(const double tlat, const double tlon, const float theight, const float frequency) override final;
  //std::vector<double> linePathloss(const double tlat, const double tlon, const float theight, const float frequency); 
  virtual void send(std::vector<double> pathloss);
};

/* NORM */
template <typename T> 
T modulo(std::vector<T> const& vec) {
    double d = vec.front() * vec.back();
    return sqrt(d);
}