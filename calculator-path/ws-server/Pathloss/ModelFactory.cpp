
#pragma once;
#include "ModelFactory.hpp"
#include "HttpGetFactory.hpp"
#include "HttpGet.hpp"

Model* ModelFactory::createModel(pmodel pm, penv pe, int tp, path corners){
    int propagationEnvironment;
    switch(pe){
        case(penv::urban):
            propagationEnvironment = 1;
            break;
        case(penv::suburban):
            propagationEnvironment = 2;
            break;
        case(penv::rural):
            propagationEnvironment = 3;
            break;
        default:
            break;
    }
    if(pm == pmodel::egli || pm == pmodel::pel || pm == pmodel::hata){    
        HttpGetFactory httpSH;
        HttpGet* httpget = httpSH.createHttpGet(corners);
        Model* model = new Model{pm, propagationEnvironment, tp, httpget};
    }
    else if(pm == pmodel::fspl){
        Model* model = new Model{pm, propagationEnvironment;
    }
    return model;
}
