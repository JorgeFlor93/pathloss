
#pragma once
#include "../json.hpp"
#include <ixwebsocket/IXWebSocketServer.h>
#include <memory>

class Websocket {
  public:
    Websocket (std::shared_ptr<ix::WebSocket> ws);
    void sendPartial (nlohmann::json out);
    void sendFinal();
    void sendNotification(int count, int total);
  private:
    std::shared_ptr<ix::WebSocket> ws;
    std::vector<nlohmann::json> acc;
};