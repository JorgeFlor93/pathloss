
#include "PathlossFactory.hpp"

enum class Type{
    Area = 0, 
    Line, 
    Point
};

IPathloss* PathlossFactory::createPathloss(std::string type, std::string model){
    /*  */    
    switch (type) {
        case (Type.Area):
        PathlossArea* pathlossarea = new PathlosssArea;
        return pathlossarea;
        break;

        // case (type  == "Line"):

        // case (type  == "Point"):

    }
}


/* 

ExecutablePathloss* executablePathloss = new ExecutablePathloss{}; 
    executablePathloss->addFixedPathloss(atributes); 
    return executablePathloss; 
    
*/