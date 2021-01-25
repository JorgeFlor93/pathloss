#include "ModelFactory.hpp"

Model* ModelFactory::createModel(pmodel pm, penv pe){
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
    Model* model = new Model{pm, propagationEnvironment};
    model->lambdaFunction();
    return model;
}
