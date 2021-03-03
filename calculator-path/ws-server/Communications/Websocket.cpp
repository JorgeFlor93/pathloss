
#include "Websocket.hpp"

Websocket::Websocket(std::shared_ptr<ix::WebSocket> ws) {
  this->ws = ws;
}

void Websocket::sendPartial (nlohmann::json out) { 
  this->acc.push_back(out);
  out["type"] = "partial";
  std::string s_out = out.dump();
  this->ws->send(s_out);
}

void Websocket::sendFinal(nlohmann::json parameters) {
  nlohmann::json j_out;
  j_out["Final"] = this->acc;
  j_out["Parameters"] = parameters;
  j_out["type"] = "final";
  std::string s_out = j_out.dump();
  this->ws->send(s_out);
}

void Websocket::sendParameters(int tp, int height, int width, int vsize, int progress, path corners){
  nlohmann::json j_out;
  j_out["parameters"] = {
    {"totalpoints", tp},
    {"height", height},
    {"width", width},
    {"numantennas", vsize},
    {"progress", progress},
    {"corners", {
      {"topleft", {
        {"lat", corners.lat1},
        {"lon", corners.lon1}
      }},
      {"botright", {
        {"lan", corners.lat2},
        {"lon", corners.lon2}
      }}
    }}
  };
  j_out["type"] = "dimensions";
  this->ws->send(j_out.dump());
}