
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
  Executable* executable = executableFactory.create(this->actions["executable"].get<std::string>(), 
                                                    this->actions["atributes"][0], 
                                                    this->actions["operands"][0]
                                                   ); //CREAR
  for (nlohmann::json::iterator action = this->actions["actions"].begin(); action != this->actions["actions"].end(); ++action) {
      executable->execute(*action); //EJECUTAR
      this->ws->sendPartial(executable->result(*action)); //ENVIAR  
  }
  //this->ws->sendFinal();
}

