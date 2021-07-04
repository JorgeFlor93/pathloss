#pragma once
#include <string>
#include <vector>
#include <functional>
#include "PathlossAbs.hpp"
#include "../Communications/Emisor.hpp"
#include "Model.hpp"
#include "../common.h"
#include "../Communications/Websocket.hpp"
#include "../json.hpp"

class PathlossArea : public PathlossAbs
{
public:
  PathlossArea(Model *model, Emisor *emisor, std::vector<double> res, path corners, int n) : model(model), emisor(emisor), resolution(res), corners(corners), n(n){};
  void onReady(std::vector<antenna> vantenna);
  virtual void calcPathloss(std::vector<antenna> &vantenna) override final;
  virtual std::vector<int> setgetDimensions(path corners, std::vector<double> resolution) override final;
  virtual nlohmann::json getParameters(std::vector<antenna> vantennas, std::vector<int> dimensions, ptAtributes atributes) override final;

private:
  Model *model;
  Emisor *emisor;
  std::vector<double> resolution;
  path corners;
  int n;
  std::function<double(const double lat, const double lon, const int pos,
                       const double tlat, const double tlon, const float theight, const float frequency)>
      algorithm;
  double bestloss;
  std::vector<int> dimensions;
};