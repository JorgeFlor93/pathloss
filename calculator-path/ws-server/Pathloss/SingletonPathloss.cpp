
#include "SingletonPathloss.hpp"

PathlossInterface* SingletonPathloss::InternalGetPathloss(Model* model, Emisor* emisor, std::vector<double> res, path corners, ptype type, int n){ 
    switch (type){
        case (ptype::Area):
        {
            std::cout << n << ":Create Singleton object:Area" << std::endl;  
            return new PathlossArea(model, emisor, res, corners, n);  
        }
        case (ptype::Line):
            std::cout << n << ":Create Singleton object:Line" << std::endl;  
            return new PathlossLine{model, emisor, res, corners};
        case (ptype::Point):
            std::cout << n << ":Create Singleton object:Point" << std::endl;  
            return  new PathlossPoint(model, emisor, res, corners);      
    }
    return nullptr;
}

