#include "lossreport.hpp"

double LossReport(struct site source, struct site destination, std::string propmodel, std::string pmenv, float freq){
    
    double dkm = 0.0;
    double loss = 0.0;
    int pmenv_int = 0;
    dkm = Distance(source, destination);
    /*CONVERT model enviaronment to int*/
    if(pmenv == "URBAN") pmenv_int = 1;
    else if(pmenv == "SUBURBAN") pmenv_int = 2;
    else if(pmenv == "OPEN") pmenv_int = 3;

    if(propmodel == "hata"){	
        //HATA 
        loss = HATApathLoss(freq, source.alt, destination.alt, dkm, pmenv_int);
    }
    else if(propmodel == "fspl"){
        // ITU-R P.525 Free space path loss
        loss = FSPLpathLoss(freq, dkm);
    }
	return loss;
}

