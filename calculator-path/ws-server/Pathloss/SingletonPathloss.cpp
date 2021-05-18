
#include "SingletonPathloss.hpp"

PathlossInterface* SingletonPathloss::InternalGetPathloss(Model* model, Emisor* emisor, std::vector<double> res, path corners, ptype type){ 
    switch (type){
        case (ptype::Area):  
            return new PathlossArea(model, emisor, res, corners);  
        case (ptype::Line):
            return new PathlossLine{model, emisor, res, corners};
        case (ptype::Point):
            return  new PathlossPoint(model, emisor, res, corners);      
    }
    return nullptr;
}

