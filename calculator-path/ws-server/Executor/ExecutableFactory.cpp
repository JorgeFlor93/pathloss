
#include "ExecutableFactory.hpp"

Executable* ExecutableFactory::create (std::string executable, nlohmann::json actions) {
  // if (executable == "calculator") {
  //   Calculator calculator{};
  //   ExecutableCalculator* executableCalculator = new ExecutableCalculator{}; //Creas decorador
  //   executableCalculator->setCalculator(calculator); //Decoras a calculator
     
  //   std::string operation = actions["operation"].get<std::string>();
  //   std::vector<double> operands = actions["operands"].get<std::vector<double>>();
  //   executableCalculator->addFixedCalculation(operation, operands);

  //   return executableCalculator;
  // } 
  // else if(executable == "matrixcalculator") {
  //   MatrixCalculator matrixcalculator{};
  //   ExecutableMatrixCalculator* executableMatrix = new ExecutableMatrixCalculator{};
  //   executableMatrix->setMatrixCalculator(matrixcalculator);

  //   std::string operation = actions["operation"].get<std::string>();
  //   std::vector<std::vector<std::vector<double>>> operands = actions["operands"].get<std::vector<std::vector<std::vector<double>>>>();
  //   executableMatrix->addFixedMatrixCalculation(operation, operands);

  //   return executableMatrix;
  // }
  if(executable == "pathloss"){
    Pathloss pathloss{};
    ExecutablePathloss* executablePathloss = new ExecutablePathloss{};
    executablePathloss->setPathloss(pathloss);

    std::string model = actions["model"].get<std::string>();
    std::string object = actions["object"].get<std::string>(); 
    nlohmann::json areaCoord = actions["areaCorners"].get<nlohmann::json>();
    executablePathloss->addFixedPathloss(model, object, areaCoord);
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