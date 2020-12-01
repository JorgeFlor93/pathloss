#pragma once
#include "IPathloss.hpp"

class AbsPathloss : public IPathloss{
public:
    void calcPathloss();
};