
#include "Executor.hpp"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void Executor::setWebSocket(Websocket* ws) {
   this->ws = ws; 
}

void Executor::setActions(std::string actions) {
  this->actions = nlohmann::json::parse(actions);
}

void Executor::execute(){
  ExecutableFactory executableFactory{this->n};
  executableFactory.create(
    this->actions["executable"].get<std::string>(), 
    this->actions["atributes"][0],
    this->ws, 
    [](Executable* executable){executable->execute();
  }); //CREAR
  std::cout << this->n << ":END" << std::endl; 
  // this->ws->sendFinal();
}
