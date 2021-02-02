
#include "Model.hpp"

std::function<double(const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)> Model::lambdaFunction(){

    float rxheight = 10; // server http get area heights
    switch(this->pm){
        case(pmodel::fspl):
            this->algorithm = [this](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
            {
                return FSPLpathLoss(frequency, calcDistance(tlat, tlon, lat, lon));
            };
            break;
        case(pmodel::hata):
            this->algorithm = [=](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
            {  
                return HATApathLoss(frequency, theight, rxheight, calcDistance(tlat, tlon, lat, lon), this->propagationEnvironment);
            };
            break;
        case(pmodel::egli):
            this->algorithm = [=/* &rxheight, this */](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
            {
                return EgliPathLoss(frequency, theight, rxheight, calcDistance(tlat, tlon, lat, lon));
            };
            break; 
        case(pmodel::pel):
            this->algorithm = [=](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
            {
                return PlaneEarthLoss(calcDistance(tlat, tlon, lat, lon), theight, rxheight);
            };
            break;
        default:
            break;
    }
    return this->algorithm;
}


double Model::calcDistance(const double tlat, const double tlon, const double lat, const double lon){

	double lat1 = tlat * DEG2RAD;
	double lon1 = tlon * DEG2RAD;
	double lat2 = lat * DEG2RAD;
	double lon2 = lon * DEG2RAD;

	double distance = 3959.0 * acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos((lon1) - (lon2)));

	return distance * KM_PER_MILE;
}
