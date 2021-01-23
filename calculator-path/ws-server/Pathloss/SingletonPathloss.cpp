
#include "SingletonPathloss.hpp"

IPathloss* SingletonPathloss::InternalGetPathloss(Algorithm* model, Emisor* emisor, ptAtributes atributes){ 
    switch (atributes.enumtype){
        case (ptype::Area):
            {
            /* Corners */
            atributes.corners.lat1 = atributes.edges["topleft"][0]["lat"].get<double>();
            atributes.corners.lon1 = atributes.edges["topleft"][0]["lon"].get<double>();
            atributes.corners.lat2 = atributes.edges["botright"][0]["lat"].get<double>();
            atributes.corners.lon2 = atributes.edges["botright"][0]["lon"].get<double>();      
            PathlossArea* pathlossarea = new PathlossArea(model, emisor, atributes);
            return pathlossarea;
            }
            break;
        case (ptype::Line):
            {
            atributes.corners.lat1 = atributes.edges["startPoint"][0]["lat"].get<double>();
            atributes.corners.lon1 = atributes.edges["startPoint"][0]["lon"].get<double>();
            atributes.corners.lat2 = atributes.edges["endPoint"][0]["lat"].get<double>();
            atributes.corners.lon2 = atributes.edges["endPoint"][0]["lon"].get<double>();
            PathlossLine* pathlossline = new PathlossLine{model, atributes};
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
}

