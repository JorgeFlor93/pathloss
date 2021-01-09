
#include "Algorithm.hpp"

void Algorithm::lambdaFunction(){

    int tipo_terreno = atributes.propagationEnv;
    float height = 10; // server http get heights
    if(atributes.propagationModel == "hata")
    {
        model = [&tipo_terreno, &height](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
        {
            return HATApathLoss(frequency, theight, height, calcDistance(tlat, tlon, lat, lon), tipo_terreno);
        };
    }    
    else if(atributes.propagationModel == "egli")
    {
        model = [&height](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
        {
            return EgliPathLoss(frequency, theight, height, calcDistance(tlat, tlon, lat, lon));
        };
    }  
    else if(atributes.propagationModel == "fspl")
    {
        model = [](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
        {
            return FSPLpathLoss(frequency, calcDistance(tlat, tlon, lat, lon));
        };  
    }
}

double calcDistance(const double tlat, const double tlon, const double lat, const double lon){

	double lat1 = tlat * DEG2RAD;
	double lon1 = tlon * DEG2RAD;
	double lat2 = lat * DEG2RAD;
	double lon2 = lon * DEG2RAD;

	double distance = 3959.0 * acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos((lon1) - (lon2)));

	return distance * KM_PER_MILE;
}

// for(Antenna& itx : this->vectorTx){ 
    //     propagation = d.get_arealoss(tl_lat, tl_lon, br_lat, br_lon, itx.getLat(), itx.getLon(), itx.getHeight(), itx.getFrequency(), model, progress);    

    //     jout.emplace_back(nlohmann::json::array({"antenna", {
    //                     {"id", itx.getId()}, 
    //                     {"type", itx.getType()},
    //                     {"lat", itx.getLat()},
    //                     {"lon", itx.getLon()},
    //                     {"height", itx.getHeight()},
    //                     {"frequency", itx.getFrequency()},
    //                     {"Area points", area_points},
    //                     {"Area Loss", propagation}}
    //                 }));   
    //                 //sendPartial?

    // }
    // return jout;