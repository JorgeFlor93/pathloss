
#pragma once
#include <ixwebsocket/IXWebSocketServer.h>
#include <memory>
#include "../json.hpp"
#include "../common.h"

class Websocket {
  public:
    Websocket (std::shared_ptr<ix::WebSocket> ws);
    void sendParameters(int tp, int height, int width, int vsize, int progress, path corners);
    void sendPartial(nlohmann::json out);
    void sendFinal(nlohmann::json parameters);
  private:
    std::shared_ptr<ix::WebSocket> ws;
    std::vector<nlohmann::json> acc;
};