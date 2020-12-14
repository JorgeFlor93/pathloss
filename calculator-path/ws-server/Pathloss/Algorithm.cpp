
#include "Algorithm.hpp"

void Algorithm::lambdaFunction(){
    // std::vector<double> propagation;
    // nlohmann::json jout;
    //int area_points = a.getTotalpoints(tl_lat, tl_lon, br_lat, br_lon); // TotalPoints
    int tipo_terreno = atributes.propagationEnv;
    float height = 100;

    // std::function<double(const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)> model;
    if(atributes.propagationModel == "hata")
    {
        model = [&tipo_terreno, &height](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
        {
            return calcHata(lat, lon, height, tlat, tlon, theight, frequency, tipo_terreno);
        };
    }
    else if(atributes.propagationModel == "fspl")
    {
        model = [](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
        {
            return calcFSPL(lat, lon, tlat, tlon, theight, frequency);
        };  
    }
    else if(atributes.propagationModel == "egli")
    {
        model = [&height](const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)
        {
            return calcEgli(lat, lon, height, tlat, tlon, theight, frequency);
        };
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
}

double calcDistance(const double tlat, const double tlon, const double lat, const double lon){

	double lat1 = tlat * DEG2RAD;
	double lon1 = tlon * DEG2RAD;
	double lat2 = lat * DEG2RAD;
	double lon2 = lon * DEG2RAD;

	double distance = 3959.0 * acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos((lon1) - (lon2)));

	return distance * KM_PER_MILE;
}

double calcHata(const double lat,const double lon, const float height, const double tlat, const double tlon, const float theight, const float frequency, const int tipo_terreno){
    return HATApathLoss(frequency, theight, height, calcDistance(tlat, tlon, lat, lon), tipo_terreno);
}
double calcFSPL(const double lat,const double lon, const double tlat, const double tlon, const float theight, const float frequency){
   return FSPLpathLoss(frequency, calcDistance(tlat, tlon, lat, lon));
}

double calcEgli(const double lat,const double lon, const float height, const double tlat, const double tlon, const float theight, const float frequency){
   return EgliPathLoss(frequency, theight, height, calcDistance(tlat, tlon, lat, lon));
}

