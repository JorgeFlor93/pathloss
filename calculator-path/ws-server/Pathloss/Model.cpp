
#include "Model.hpp"
#include <iostream>
#include "models/fspl.hh"
#include "models/hata.hh"
#include "models/egli.hh"
#include "models/pel.hh"
#include "models/cost.hh"
#include "models/ecc33.hh"
#include "models/soil.hh"
#include "models/sui.hh"
#include "models/ericsson.hh"
#include "models/itwom3.0.hh"

class ExecuteOnExit
{
private:
    using ToExecute = std::function<void(void)>;
    ToExecute toExecute;
public:
    ExecuteOnExit(ToExecute&& toExecute) : toExecute(std::move(toExecute)){}
    ~ExecuteOnExit(){/* std::cout << "preexecute" << std::endl; */ toExecute(); /* std::cout << "\npostexecute\n" << std::endl; */}
};

Model::Algorithm Model::createAlgorithm(HttpGet::OnReady onReady)
{ 
    switch(this->pm){
        case(pmodel::fspl):
        {     
         
            return  [this](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
            {
                return FSPLpathLoss(frequency, calcDistance(tlat, tlon, lat, lon));
            };
        }
        case(pmodel::hata):
        {  
            
            ExecuteOnExit e([this, onReady](){this->httpget->request(onReady);}); // request de las alturas del área
            return [=](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
            {  
                return HATApathLoss(frequency, theight, this->httpget->get()[pos], calcDistance(tlat, tlon, lat, lon), this->propagationEnvironment);
            };
        }
        case(pmodel::egli):
        {
            
            ExecuteOnExit e([this, onReady](){this->httpget->request(onReady);}); // request de las alturas del área
            return [=](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
            {
                return EgliPathLoss(frequency, theight, this->httpget->get()[pos], calcDistance(tlat, tlon, lat, lon));
            };
        }
        case(pmodel::pel):
        {
            
            ExecuteOnExit e([this, onReady](){this->httpget->request(onReady);}); // request de las alturas del área
            return  [=](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
            {
                return PlaneEarthLoss(calcDistance(tlat, tlon, lat, lon), theight, this->httpget->get()[pos]);
            };
        }
        case(pmodel::cost):
        {
            
            ExecuteOnExit e([this, onReady](){this->httpget->request(onReady);}); // request de las alturas del área
            return  [=](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
            {
                return COST231pathLoss(frequency, theight, this->httpget->get()[pos], calcDistance(tlat, tlon, lat, lon), this->propagationEnvironment);
            };
        }
        case(pmodel::ecc33):
        {
            
            ExecuteOnExit e([this, onReady](){this->httpget->request(onReady);}); // request de las alturas del área
            return  [=](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
            {
                return ECC33pathLoss(frequency, theight, this->httpget->get()[pos], calcDistance(tlat, tlon, lat, lon), this->propagationEnvironment);
            };
        }
        case(pmodel::ericcson):
        {
         
            ExecuteOnExit e([this, onReady](){this->httpget->request(onReady);}); // request de las alturas del área
            return  [=](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
            {
                return EricssonpathLoss(frequency, theight, this->httpget->get()[pos], calcDistance(tlat, tlon, lat, lon), this->propagationEnvironment);
            };
        }
        case(pmodel::itwom):
        {
         
            ExecuteOnExit e([this, onReady](){this->httpget->request(onReady);}); // request de las alturas del área
            return  [=](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
            {
                return point_to_point(theight, this->httpget->get()[pos], 20, 0.0001, 300, frequency, 7, 0, 0.5, 0.5);
            };
        }
        case(pmodel::soil):
        {
            
            return  [=](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
            {
                return SoilPathLoss(frequency, calcDistance(tlat, tlon, lat, lon), 50);
            };
        }
        case(pmodel::sui):
        {
            
            ExecuteOnExit e([this, onReady](){this->httpget->request(onReady);}); // request de las alturas del área
            return  [=](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
            {
                return SUIpathLoss(frequency, theight, this->httpget->get()[pos], calcDistance(tlat, tlon, lat, lon), this->propagationEnvironment);
            };
        }
    }
    std::cout << "Modelo no encontrado" << std::endl;
    return nullptr;
}


double Model::calcDistance(const double tlat, const double tlon, const double lat, const double lon){

	double lat1 = tlat * DEG2RAD;
	double lon1 = tlon * DEG2RAD;
	double lat2 = lat * DEG2RAD;
	double lon2 = lon * DEG2RAD;

	double distance = 3959.0 * acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos((lon1) - (lon2)));

	return distance * KM_PER_MILE;
}

pmodel Model::getModel(){
    return this->pm;
}

std::string Model::getModelName(){
    return this->modelName;
}