
#pragma once
#include "ExecutableFactory.hpp"
#include "Executable.hpp"
#include "../Communications/Websocket.hpp"
#include "../json.hpp"

class Executor {
  public:
    void setWebSocket(Websocket* ws);
    void setActions(std::string actions);
    void execute();
  private:
    Websocket* ws;
    nlohmann::json actions;
};
