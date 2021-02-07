
#include "Executor.hpp"

void Executor::setWebSocket(Websocket* ws) {
   this->ws = ws; 
}

void Executor::setActions(std::string actions) {
  this->actions = nlohmann::json::parse(actions);
}

void Executor::execute(){
  ExecutableFactory executableFactory;
  Executable* executable = executableFactory.create(this->actions["executable"].get<std::string>(), this->actions["atributes"][0], this->ws); //CREAR
  executable->execute(); //EJECUTAR
  this->ws->sendFinal();
}

