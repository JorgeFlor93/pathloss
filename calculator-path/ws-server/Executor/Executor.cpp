
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
  Executable* executable = executableFactory.create(this->actions["executable"].get<std::string>(), this->actions["atributes"][0], this->actions["actions"][0]); //CREAR
  std::vector<std::string> aux = this->actions["actions"][0]["operation"].get<std::vector<std::string>>();
  // for (nlohmann::json::iterator action = this->actions["actions"].begin(); action != this->actions["actions"].end(); ++action) {
    for(std::vector<std::string>::iterator it = aux.begin(); it != aux.end(); ++it){
      executable->execute(*it); //EJECUTAR
      this->ws->sendPartial(executable->result()); //ENVIAR
    }
  //}
  this->ws->sendFinal();
}

