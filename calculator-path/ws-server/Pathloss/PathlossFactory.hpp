#pragma once
#include <string>
#include "PathlossArea.hpp"

class PathlossFactory{
    IPathloss* createPathloss(std::string type, std::string model);
};