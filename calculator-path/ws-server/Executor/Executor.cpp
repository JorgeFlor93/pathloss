
#include "Executor.hpp"

void Executor::setWebSocket(Websocket* ws) {
   this->ws = ws; 
}

void Executor::setActions(std::string actions) {
  this->actions = nlohmann::json::parse(actions);
}

void Executor::execute(){
  ExecutableFactory executableFactory;
  executableFactory.create(
    this->actions["executable"].get<std::string>(), 
    this->actions["atributes"][0],
    this->ws, 
    [](Executable* executable){executable->execute();
  }); //CREAR
  std::cout << "final" << std::endl; 
  // this->ws->sendFinal();
}
