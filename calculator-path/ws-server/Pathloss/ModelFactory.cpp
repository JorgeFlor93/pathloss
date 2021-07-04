
#include "ModelFactory.hpp"
#include "../Communications/HttpGetArea.hpp"
#include <iostream>

Model* ModelFactory::createModel(pmodel pm, penv pe, path corners, int n){
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
        std::cout << n << ":Create Model object:egli" << std::endl;  
        return new Model{pm, propagationEnvironment, n, new HttpGetArea{corners, n}, "egli"};
    case (pmodel::fspl):
        std::cout << n << ":Create Model object:fspl" << std::endl;  
        return new Model{pm, propagationEnvironment, n, "fspl"};
    case (pmodel::soil):
        std::cout << n << ":Create Model object:soil" << std::endl;  
        return new Model{pm, propagationEnvironment, n, "soil"};
    case (pmodel::sui):
        std::cout << n << ":Create Model object:sui" << std::endl;  
        return new Model{pm, propagationEnvironment, n, new HttpGetArea{corners, n}, "sui"};
    case (pmodel::ericcson):
        std::cout << n << ":Create Model object:ericsson" << std::endl;  
        return new Model{pm, propagationEnvironment, n, new HttpGetArea{corners, n}, "ericsson"};
    case (pmodel::ecc33):
        std::cout << n << ":Create Model object:ecc33" << std::endl;  
        return new Model{pm, propagationEnvironment, n, new HttpGetArea{corners, n}, "ec33"};
    case (pmodel::cost):
        std::cout << n << ":Create Model object:cost" << std::endl;  
        return new Model{pm, propagationEnvironment, n, new HttpGetArea{corners, n}, "cost"};
    case (pmodel::hata):
        std::cout << n << ":Create Model object:hata" << std::endl;  
        return new Model{pm, propagationEnvironment, n, new HttpGetArea{corners, n}, "hata"};
    case (pmodel::itwom):
        std::cout << n << ":Create Model object:itwom" << std::endl;  
        return new Model{pm, propagationEnvironment, n, new HttpGetArea{corners, n}, "itwom"};
    case (pmodel::pel):
        std::cout << n << ":Create Model object:pel" << std::endl;  
        return new Model{pm, propagationEnvironment, n, new HttpGetArea{corners, n}, "pel"};
    }
    return nullptr;
}