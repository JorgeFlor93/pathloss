
#include "SingletonPathloss.hpp"

IPathloss* SingletonPathloss::InternalGetPathloss(Model* model, Emisor* emisor, std::vector<double> res, path corners, ptype type){ 
    switch (type){
        case (ptype::Area):
            {   
            PathlossArea* pathlossarea = new PathlossArea(model, emisor, res, corners);
            return pathlossarea;
            }
            break;
        case (ptype::Line):
            {
            PathlossLine* pathlossline = new PathlossLine{model, emisor, res, corners};
            return pathlossline;
            }
            break;
        case (ptype::Point):
            {
            
            }
            return nullptr;
            break;
        
        default:
            return nullptr;
            break;
    }
    return nullptr;
}

