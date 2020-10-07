
#pragma once
#include <string>
#include <vector>
#include "../json.hpp"

class Executable {
  public:
    virtual ~Executable(){};
    virtual void execute(nlohmann::json work) = 0;
    virtual nlohmann::json result(nlohmann::json f) = 0;
};