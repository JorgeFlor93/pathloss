#pragma once
#include <string>
#include "PathlossArea.hpp"
#include "PathlossLine.hpp"
#include "IPathloss.hpp"
#include "../common.h"
#include "../json.hpp"
#include "Algorithm.hpp"
#include <stdlib.h>

class SingletonPathloss{
public:
    SingletonPathloss(const SingletonPathloss&) = delete;
    void operator=(const SingletonPathloss&) = delete;
    static SingletonPathloss& Get(){
        static SingletonPathloss instance; 
        return instance;
    }
    static IPathloss* getPathloss(Algorithm* model, ptAtributes atributes){ 
        return Get().InternalGetPathloss(model, atributes); 
    }
private:
    IPathloss* InternalGetPathloss(Algorithm* model, ptAtributes atributes);
    SingletonPathloss(){};
};