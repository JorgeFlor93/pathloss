
#include "ModelFactory.hpp"

Model* ModelFactory::createModel(pmodel pm, penv pe, path corners, Websocket* ws){
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
        Model* model = new Model{pm, propagationEnvironment, httpSH.createHttpGet(corners, ws)};
        return model;
    }
    else if(pm == pmodel::fspl){
        Model* model = new Model{pm, propagationEnvironment};
        return model;
    }
    return NULL;
}
