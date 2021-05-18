
#include "Model.hpp"
#include <iostream>
#include "models/fspl.hh"
#include "models/hata.hh"
#include "models/egli.hh"
#include "models/pel.hh"

class ExecuteOnExit
{
private:
    using ToExecute = std::function<void(void)>;
    ToExecute toExecute;
public:
    ExecuteOnExit(ToExecute&& toExecute) : toExecute(std::move(toExecute)){}
    ~ExecuteOnExit(){std::cout << "preexecute" << std::endl; toExecute(); std::cout << "\npostexecute\n" << std::endl;}
};

Model::Algorithm Model::createAlgorithm(HttpGet::OnReady onReady)
{
    std::cout << "1" << std::endl;   
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
            this->httpget->request(onReady); 
            return [=](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
            {
                return EgliPathLoss(frequency, theight, this->httpget->get()[pos], calcDistance(tlat, tlon, lat, lon));
            };
        }
        case(pmodel::pel):
        {
            this->httpget->request(onReady);
            return  [=](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
            {
                return PlaneEarthLoss(calcDistance(tlat, tlon, lat, lon), theight, this->httpget->get()[pos]);
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
