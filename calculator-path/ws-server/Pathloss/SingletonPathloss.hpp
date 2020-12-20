#pragma once
#include <string>
#include "PathlossArea.hpp"
#include "IPathloss.hpp"
#include "../common.h"
#include "../json.hpp"

class SingletonPathloss{
public:
    SingletonPathloss(const SingletonPathloss&) = delete;
    void operator=(const SingletonPathloss&) = delete;
    static SingletonPathloss& Get(){
        static SingletonPathloss instance; 
        return instance;
    }
    static IPathloss* getPathloss(){ return Get().InternalGetPathloss(); }
private:
    IPathloss* InternalGetPathloss();
    SingletonPathloss(){};
};