#pragma once
#include <string>
#include <vector>
#include "../json.hpp"
#include <ixwebsocket/IXWebSocketServer.h>
#include "../Communications/Websocket.hpp"

class Executable {
  public:
    virtual ~Executable(){};
    virtual void execute() = 0;
    virtual nlohmann::json result() = 0;
};