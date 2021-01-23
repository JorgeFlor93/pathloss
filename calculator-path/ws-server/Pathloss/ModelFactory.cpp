#include "ModelFactory.hpp"

Algorithm* ModelFactory::createModel(pmodel pm, penv pe){
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
    Algorithm* model = new Algorithm{pm, propagationEnvironment};
    model->lambdaFunction();
    return model;
}
