
#include "SingletonPathloss.hpp"

// enum PathlossType {
//     Area = 0,
//     Line,
//     Point
// };

IPathloss* SingletonPathloss::InternalGetPathloss(){ 
    if(atributes.type == "Area"){
        /* Corners */
        corner.lat1 = atributes.calcType["topleft"][0]["lat"].get<double>();
        corner.lon1 = atributes.calcType["topleft"][0]["lon"].get<double>();
        corner.lat2 = atributes.calcType["botright"][0]["lat"].get<double>();
        corner.lon2 = atributes.calcType["botright"][0]["lon"].get<double>();
        
        PathlossArea* pathlossarea = new PathlossArea{};
        return pathlossarea;
    }
    else if(atributes.type == "Point"){}
    else if(atributes.type == "Line"){}
    
    // switch (atributes.type) {
    //     case ("Area"):
        
    //     break;

        // case (type  == "Line"):
        // break;

        // case (type  == "Point"):
        // break;
    // }
    return nullptr;
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
*/