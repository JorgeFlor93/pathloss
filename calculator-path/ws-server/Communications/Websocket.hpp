
#pragma once
#include <ixwebsocket/IXWebSocketServer.h>
#include <memory>
#include "../json.hpp"

class Websocket {
  public:
    Websocket (std::shared_ptr<ix::WebSocket> ws);
    void sendPartial(nlohmann::json out);
    void sendFinal();
  private:
    std::shared_ptr<ix::WebSocket> ws;
    std::vector<nlohmann::json> acc;
};