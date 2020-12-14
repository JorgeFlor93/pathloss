#pragma once

class IPathloss{
public:
virtual ~IPathloss(){};
virtual void calcPathloss() = 0; 
virtual void lambdaFunction() = 0;
};