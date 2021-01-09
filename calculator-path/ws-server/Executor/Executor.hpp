
#pragma once
#include <string>
#include "ExecutableFactory.hpp"
#include "Executable.hpp"
#include "../Communications/Websocket.hpp"
#include "../json.hpp"


class Executor {
  public:
    void setWebSocket(Websocket* ws);
    void setActions(std::string actions);
    virtual void execute();
  private:
    Websocket* ws;
    nlohmann::json actions;
};
