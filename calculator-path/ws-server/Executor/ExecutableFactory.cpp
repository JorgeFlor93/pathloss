
#include "ExecutableFactory.hpp"

Executable* ExecutableFactory::create (std::string executable, nlohmann::json atributes, nlohmann::json operands) {
  if(executable == "pathloss"){
    Pathloss pathloss{};
    ExecutablePathloss* executablePathloss = new ExecutablePathloss{};
    executablePathloss->setPathloss(pathloss);
    executablePathloss->addFixedPathloss(atributes, operands);
    return executablePathloss;
  }
  else {
    return nullptr;
  }
}

/*
for (nlohmann::json::iterator action = this->actions["actions"].begin(); action != this->actions["actions"].end(); ++action) {
    std::string operation = (*action)["operation"].get<std::string>();
    double out = executable->execute(operation); //Se llama a execute

std::string s = j.dump();    // {"happy":true,"pi":3.141}

// serialization with pretty printing
// pass in the amount of spaces to indent
std::cout << j.dump(4) << std::endl;
    
*/