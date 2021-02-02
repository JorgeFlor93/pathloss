#pragma once
#include <string>
#include "PathlossArea.hpp"
#include "PathlossLine.hpp"
#include "PathlossPoint.hpp"
#include "IPathloss.hpp"
#include "../common.h"
#include "../json.hpp"
#include "Model.hpp"
#include "Emisor.hpp"

#include <stdlib.h>

class SingletonPathloss{
public:
    SingletonPathloss(const SingletonPathloss&) = delete;
    void operator=(const SingletonPathloss&) = delete;
    static SingletonPathloss& Get(){
        static SingletonPathloss instance; 
        return instance;
    }
    static IPathloss* getPathloss(Model* model, Emisor* emisor, std::vector<double> res, path corners, ptype type){ 
        return Get().InternalGetPathloss(model, emisor, res, corners, type); 
    }
private:
    IPathloss* InternalGetPathloss(Model* model, Emisor* emisor, std::vector<double> res, path corners, ptype type);
    SingletonPathloss(){};
};