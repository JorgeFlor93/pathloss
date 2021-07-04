
#include "Websocket.hpp"
#include <iostream>

void Websocket::sendInitial (nlohmann::json out) { 
  std::cout << this->n << ":Sending parameters" << std::endl;  
  nlohmann::json j_out;
  j_out["Parameters"] = out;
  j_out["type"] = "initial";
  std::string s_out = j_out.dump();
  this->ws->send(s_out);
}

void Websocket::sendPartial (nlohmann::json out) { 
  // SendPartial acumula cada envío parcial en la variable acc
  this->acc.push_back(out);
  out["type"] = "partial";
  std::string s_out = out.dump();
  std::cout << this->n << ":Sending Partial calculus" << std::endl;  
  this->ws->send(s_out);
}

void Websocket::sendFinal() {
  nlohmann::json j_out;
  j_out["Final"] = this->acc;
  j_out["type"] = "final";
  std::string s_out = j_out.dump();
  std::cout << this->n << ":Sending All calculus" << std::endl;  
  this->ws->send(s_out);
}


/* Para la depuración del código */
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