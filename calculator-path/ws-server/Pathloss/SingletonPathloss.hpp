#pragma once
#include "PathlossArea.hpp"
#include "PathlossLine.hpp"
#include "PathlossPoint.hpp"
#include "PathlossInterface.hpp"
#include "../common.h"
#include "../json.hpp"
#include "Model.hpp"
#include "../Communications/Emisor.hpp"


class SingletonPathloss{
public:
    SingletonPathloss(const SingletonPathloss&) = delete;
    void operator=(const SingletonPathloss&) = delete;
    static SingletonPathloss& Get(){
        static SingletonPathloss instance; 
        return instance;
    }
    static PathlossInterface* getPathloss(Model* model, Emisor* emisor, std::vector<double> res, path corners, ptype type, int n){ 
        return Get().InternalGetPathloss(model, emisor, res, corners, type, n); 
    }
private:
    PathlossInterface* InternalGetPathloss(Model* model, Emisor* emisor, std::vector<double> res, path corners, ptype type, int n);
    SingletonPathloss(){};
};