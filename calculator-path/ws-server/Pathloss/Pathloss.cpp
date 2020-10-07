#include "Pathloss.hpp"

std::vector<std::vector<double>> Pathloss::displayArea(nlohmann::json varea){
    setArea(varea["topleft"].get<std::vector<double>>(), varea["botright"].get<std::vector<double>>());
    return getvectorArea();
}

std::vector<std::vector<double>> Pathloss::displayvTx(std::vector<std::vector<double>> vTx){
    return vTx;
}

void Pathloss::setArea(std::vector<double> tl, std::vector<double> br){
    this->varea = get_area(tl[0], tl[1], br[0], br[1], tl[2]/*or br[2]*/);
}

std::vector<Coord> Pathloss::getArea(){
    return this->varea;
}

std::vector<std::vector<double>> Pathloss::getvectorArea(){ //Conversor std::vector<Coord> TO std::vector<std::vector<double>>
    std::vector<std::vector<double>> vector;
    std::vector<double> coord;
    for (std::vector<Coord>::iterator it = this->varea.begin(); it != this->varea.end(); ++it){
        coord.push_back(it->getLat());
        coord.push_back(it->getdisLon());
        coord.push_back(it->getTxalt());
        vector.push_back(coord);
        coord.clear();
    }
    return vector;
}

void Pathloss::setCalculus(float freq, std::string prop_model, std::string env_mode, nlohmann::json areaCoord, std::vector<std::vector<double>> vTx, std::vector<double> points){
    std::vector<Coord> vTxcoord;
    Coord p; 
    Coord nearRx;
    Pairtxrx vtrx;
    std::vector<Pairtxrx> vpairs; // vector de pares tx-rx

    /*SET AREA*/
    // vector of vector vTx TO vector<Coord>  
    for(std::vector<std::vector<double>>::iterator it = vTx.begin(); it != vTx.end(); ++it){ 
        p.assignCoord(it->at(0), it->at(1), it->at(2));
        vTxcoord.push_back(p);
    }
    this->vTx = vTxcoord;
    setArea(areaCoord["topleft"].get<std::vector<double>>(), areaCoord["botright"].get<std::vector<double>>()); //set varea
    this->freq = freq;
    this->model = prop_model;
    this->env_mode = env_mode;

}

std::vector<double> Pathloss::getBestTx(std::vector<double> point){
    Coord p;
    Coord nearRx;
    double min_dkm = 99999;
    double curr_dkm;
    double minloss = 99999;
    bool result;
    std::vector<double> ret;
    struct site a;
    Pairtxrx vtrx;
    std::vector<Pairtxrx> vpairs;
    
    /*points vector to Coord type*/
    p.assignCoord(point.at(0), point.at(1), point.at(2));
    /*Distancia mas cercana al área*/
    for(long unsigned int j = 0; j < this->varea.size(); j++){
        curr_dkm = Distance(p.getStruct(), this->varea.at(j).getStruct());
        if(curr_dkm < min_dkm){
            min_dkm = curr_dkm;
            nearRx = this->varea.at(j);
        }
    }  
    /*Best Antenna*/
    for(auto it = this->vTx.begin(); it != this->vTx.end(); ++it){ //Por cada antena se calculan las pérdidas al área
        vtrx.setTx(it->getStruct());
        vtrx.setRx(nearRx.getStruct());
        vtrx.setLoss(this->freq, this->model, this->env_mode);
        vpairs.push_back(vtrx); 
        if(vtrx.getLoss() < minloss){
            minloss = vtrx.getLoss();
            result = nearRx.assignTx(minloss, it->getStruct());
        }
    }
    // this->ptrx = vpairs;
    a = nearRx.getBtx();    
    a.loss = nearRx.getBtxloss();
    ret.push_back(a.lat);
    ret.push_back(a.dislon);
    ret.push_back(a.txalt);
    //ret.push_back(a.loss);
    return ret;
}

// std::vector<Pairtxrx> Pathloss::getPtrx(){
//     return this->ptrx;
// }

std::vector<std::vector<double>> Pathloss::setAreaLoss(std::vector<double> tx){
    std::vector<std::vector<double>> arealoss;
    std::vector<double> aux;
    Pairtxrx ptrx;
    Coord p;

    p.assignCoord(tx.at(0), tx.at(1), tx.at(2));
    arealoss.push_back(tx);
    for(auto itb = this->varea.begin(); itb != this->varea.end(); ++itb){
        ptrx.setTx(p.getStruct());
        ptrx.setRx(itb->getStruct());
        ptrx.setLoss(this->freq, this->model, this->env_mode); 
        aux.push_back(ptrx.getRx().getLat());
        aux.push_back(ptrx.getRx().getdisLon());
        aux.push_back(ptrx.getLoss());
        arealoss.push_back(aux);
        //INTRODUCIR VALORES DEL AREA Y DEVOLVER
    }
    return arealoss;
}

std::vector<std::vector<double>> Pathloss::getAllTxLoss(std::vector<std::vector<double>> vTx, std::vector<double> points){
    Coord closeRx;
    Coord p;
    Coord AntTx;
    std::vector<std::vector<double>> arealoss;
    std::vector<double> aux;
    Pairtxrx ptrx;
    double min_dkm = 99999;
    double curr_dkm;

    /*points vector to Coord type*/
    p.assignCoord(points.at(0), points.at(1), points.at(2));
    /*Distancia mas cercana al área*/
    for(long unsigned int j = 0; j < this->varea.size(); j++){
        curr_dkm = Distance(p.getStruct(), this->varea.at(j).getStruct());
        if(curr_dkm < min_dkm){
            min_dkm = curr_dkm;
            closeRx = this->varea.at(j);
        }
    }  

    for(auto it = vTx.begin(); it != vTx.end(); ++it){ //Por cada antena se calculan las pérdidas al área
        p.assignCoord(it->at(0),it->at(1),it->at(2));
        ptrx.setTx(p.getStruct());
        ptrx.setRx(closeRx.getStruct());
        ptrx.setLoss(this->freq, this->model, this->env_mode);
        // aux.push_back(closeRx.getLat());
        // aux.push_back(closeRx.getdisLon());
        // aux.push_back(closeRx.getTxalt());
        // aux.push_back(ptrx.getLoss());
        // arealoss.push_back(aux);
        it->push_back(ptrx.getLoss());
        arealoss.push_back(*it);
        aux.clear();
    }
    return arealoss;
}

 nlohmann::json wsHttpR(){
     std::vector<std::vector<double>> varea = getvectorArea();
     int result = 0;
     result = ws_http_client_main(const std::string& url,
                                const std::string& headersData,
                                const std::string& data,
                                bool headersOnly,
                                int connectTimeout,
                                int transferTimeout,
                                bool followRedirects,
                                int maxRedirects,
                                bool verbose,
                                bool save,
                                const std::string& output,
                                bool compress,
                                const ix::SocketTLSOptions& tlsOptions
     );
//      int ws_http_client_main(const std::string& url,
//                             const std::string& headersData,
//                             const std::string& data,
//                             bool headersOnly,
//                             int connectTimeout,
//                             int transferTimeout,
//                             bool followRedirects,
//                             int maxRedirects,
//                             bool verbose,
//                             bool save,
//                             const std::string& output,
//                             bool compress,
//                             const ix::SocketTLSOptions& tlsOptions)
//  }

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

