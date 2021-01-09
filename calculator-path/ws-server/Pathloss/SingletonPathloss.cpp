
#include "SingletonPathloss.hpp"

// enum PathlossType {
//     Area = 0,
//     Line,
//     Point
// };

IPathloss* SingletonPathloss::InternalGetPathloss(){ 
    if(atributes.type == "area"){
        /* Corners */
        corner.lat1 = atributes.edges["topleft"][0]["lat"].get<double>();
        corner.lon1 = atributes.edges["topleft"][0]["lon"].get<double>();
        corner.lat2 = atributes.edges["botright"][0]["lat"].get<double>();
        corner.lon2 = atributes.edges["botright"][0]["lon"].get<double>();
        
        PathlossArea* pathlossarea = new PathlossArea{};
        return pathlossarea;
    }
    else if(atributes.type == "line"){
        corner.lat1 = atributes.edges["startPoint"][0]["lat"].get<double>();
        corner.lon1 = atributes.edges["startPoint"][0]["lon"].get<double>();
        corner.lat2 = atributes.edges["endPoint"][0]["lat"].get<double>();
        corner.lon2 = atributes.edges["endPoint"][0]["lon"].get<double>();

        PathlossLine* pathlossline = new PathlossLine{};
        return pathlossline;
        
    }
    else if(atributes.type == "point"){

    }
    else{    
        return nullptr;
    }
}
/* 

ExecutablePathloss* executablePathloss = new ExecutablePathloss{}; 
    executablePathloss->addFixedPathloss(atributes); 
    return executablePathloss; 
    
enum Color { red, green, blue };
Color r = red;
switch(r)
{
    case red  : std::cout << "red\n";   break;
    case green: std::cout << "green\n"; break;
    case blue : std::cout << "blue\n";  break;
}


switch (atributes.type) {
        case ("Area"):
        
        break;

        case (type  == "Line"):
        break;

        case (type  == "Point"):
        break;
    }
*/