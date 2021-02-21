
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

void Websocket::sendFinal () {
  nlohmann::json j_out;
  j_out["Final"] = this->acc;
  j_out["type"] = "final";
  std::string s_out = j_out.dump();
  this->ws->send(s_out);
}

void Websocket::sendDimensions(int tp, int height, int width, int vsize, int progress){
  nlohmann::json j_out;
  j_out["parameters"] = {
    {"total_points", tp},
    {"height", height},
    {"width", width},
    {"Nº Antennas", vsize},
    {"Progress (%)", progress}
  };
  j_out["type"] = "dimensions";
  this->ws->send(j_out.dump());
}