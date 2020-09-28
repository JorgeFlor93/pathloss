
#pragma once
#include <string>
#include <vector>
#include "../json.hpp"

class Executable {
  public:
    virtual ~Executable(){};
    virtual void execute() = 0;
    virtual nlohmann::json result() = 0;
};