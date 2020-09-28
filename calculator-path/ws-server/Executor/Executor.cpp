

#include "Executor.hpp"
#include <iostream>

void Executor::setWebSocket(Websocket* ws) {
  this->ws = ws;
}

void Executor::setActions(std::string actions) {
  this->actions = nlohmann::json::parse(actions);
}

void Executor::execute() {
  ExecutableFactory executableFactory{};
  for (nlohmann::json::iterator action = this->actions["actions"].begin(); action != this->actions["actions"].end(); ++action) {
    Executable* executable = executableFactory.create(this->actions["executable"].get<std::string>(), (*action)); //CREAR
    executable->execute(); //EJECUTAR
    this->ws->sendPartial(executable->result()); //ENVIAR
  }
  this->ws->sendFinal();
}

