#include "lossreport.hpp"
#include "common.h"

double LossReport(struct site source, struct site destination, float freq, std::string pm, std::string pmenv){
    
    double dkm = 0.0;
    double loss = 0.0;
    int pmenv_int = 0;
    dkm = Distance(source, destination);
    /*CONVERT model enviaronment to int*/
    if(pmenv == "URBAN") pmenv_int = 1;
    else if(pmenv == "SUBURBAN") pmenv_int = 2;
    else if(pmenv == "OPEN") pmenv_int = 3;

    if(pm == "hata"){	
        //HATA 
        loss = HATApathLoss(freq, source.alt, destination.alt, dkm, pmenv_int);
    }
    else if(pm == "fspl"){
        // ITU-R P.525 Free space path loss
        loss = FSPLpathLoss(freq, dkm);
    }
	return loss;
}

/*FUNCIONES AUXILIARES*/

double miles_to_km(double miles){   
    return miles*1.60934;
}

double Distance(struct site site1, struct site site2)
{

	double lat1, lon1, lat2, lon2, distance;

	lat1 = site1.lat * DEG2RAD;
	lon1 = site1.lon * DEG2RAD;
	lat2 = site2.lat * DEG2RAD;
	lon2 = site2.lon * DEG2RAD;

	distance =
	    3959.0 * acos(sin(lat1) * sin(lat2) +
			  cos(lat1) * cos(lat2) * cos((lon1) - (lon2)));

	distance = miles_to_km(distance);
	return distance;
}