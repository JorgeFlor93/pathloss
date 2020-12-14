#pragma once   
#include <vector>
#include "AbsPathloss.hpp"
#include "../common.h"

class Emisor : public AbsPathloss{
public:
virtual void send(std::vector<double> pathloss) override final;
};