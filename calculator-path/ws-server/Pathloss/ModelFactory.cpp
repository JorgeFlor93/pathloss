
#include "ModelFactory.hpp"
#include "HttpGetArea.hpp"

Model* ModelFactory::createModel(pmodel pm, penv pe, path corners){
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
    switch (pm)
    {
    case (pmodel::egli):
        return new Model{pm, propagationEnvironment, new HttpGetArea{corners}};
    case (pmodel::fspl):
        return new Model{pm, propagationEnvironment};
    case (pmodel::hata):
        return new Model{pm, propagationEnvironment, new HttpGetArea{corners}};
    case (pmodel::pel):
        return new Model{pm, propagationEnvironment, new HttpGetArea{corners}};
    }
    return nullptr;
}