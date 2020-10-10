#include "Pathloss.hpp"


void Pathloss::setArea(std::vector<double> tl, std::vector<double> br){
    this->varea = get_area(tl[0], tl[1], br[0], br[1], 1/*Altura del receptor*/);
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

std::vector<antenna> Pathloss::setCalculus(nlohmann::json atributes)
{   
    this->model = atributes["model"].get<std::string>();
    this->env_mode = atributes["propagation_model"].get<std::string>();
    antenna aux;
    for(nlohmann::json::iterator it = atributes["antennas"].begin(); it != atributes["antennas"].end(); ++it)
    {
        aux.setParameters((*it)["lat"].get<double>(), 
                          (*it)["lon"].get<double>(), 
                          (*it)["height"].get<float>(),
                          (*it)["type"].get<std::string>(),
                          (*it)["id"].get<std::string>(),
                          (*it)["frequency"].get<float>()
                          );
        this->vTx.push_back(aux);
    }

    /*setType*/
    if(atributes["location"][0]["type"].get<std::string>() == "area"){ /*setAREA*/
        this->type = "area";
        setArea(atributes["location"][0]["topleft"].get<std::vector<double>>(), 
                atributes["location"][0]["botright"].get<std::vector<double>>()); //set varea
    }
    // else if (){} /*setLINE*/

    return this->vTx;
}

// 

// std::vector<Pairtxrx> Pathloss::getPtrx(){
//     return this->ptrx;
// }

nlohmann::json Pathloss::setAreaLoss(){
    double loss;
    nlohmann::json jout;
    nlohmann::json aux;
    nlohmann::json areaPoint;
    for(auto itx = this->vTx.begin(); itx != this->vTx.end(); ++itx){  
        aux["antenna"] = { 
                        {"id", itx->getId()}, 
                        {"type", itx->getType()},
                        {"lat", itx->getLat()},
                        {"lon", itx->getLon()},
                        {"height", itx->getHeight()},
                        {"frequency", itx->getFrequency()}
                        // {"AreaLoss",  {"Point",  {"lat", 10}, {"lon", 1}, {"LOSS", 5} } }
                        };
        for(auto it = this->varea.begin(); it != this->varea.end(); ++it){
            loss = Loss(*itx, *it); 
            areaPoint["Point"] = { 
                                {"lat", it->getLat()} , 
                                {"lon", it->getdisLon()}, 
                                {"loss", loss} 
                                };
            aux.push_back(areaPoint);
            areaPoint.clear();
        }  
        
        
        jout.push_back(aux); 
        aux.clear();     
    }
    return jout;
}
// std::vector<std::uint8_t> v = {'t', 'r', 'u', 'e'};
// json j = json::parse(v.begin(), v.end());

double Pathloss::Loss(antenna tx, Coord rx){
    return LossReport(tx.getStruct(), rx.getStruct(), this->model, this->env_mode, tx.getFrequency());
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
// std::vector<double> Pathloss::getBestTx(std::vector<double> point){
//     Coord p;
//     Coord nearRx;
//     double min_dkm = 99999;
//     double curr_dkm;
//     double minloss = 99999;
//     bool result;
//     std::vector<double> ret;
//     struct site a;
//     Pairtxrx vtrx;
//     std::vector<Pairtxrx> vpairs;
    
//     /*points vector to Coord type*/
//     p.assignCoord(point.at(0), point.at(1), point.at(2));
//     /*Distancia mas cercana al área*/
//     for(long unsigned int j = 0; j < this->varea.size(); j++){
//         curr_dkm = Distance(p.getStruct(), this->varea.at(j).getStruct());
//         if(curr_dkm < min_dkm){
//             min_dkm = curr_dkm;
//             nearRx = this->varea.at(j);
//         }
//     }  
//     /*Best Antenna*/
//     for(auto it = this->vTx.begin(); it != this->vTx.end(); ++it){ //Por cada antena se calculan las pérdidas al punto
//         vtrx.setTx(it->getStruct());
//         vtrx.setRx(nearRx.getStruct());
//         vtrx.setLoss(this->freq, this->model, this->env_mode);
//         vpairs.push_back(vtrx); 
//         if(vtrx.getLoss() < minloss){
//             minloss = vtrx.getLoss();
//             result = nearRx.assignTx(minloss, it->getStruct());
//         }
//     }
//     // this->ptrx = vpairs;
//     a = nearRx.getBtx();    
//     a.loss = nearRx.getBtxloss();
//     ret.push_back(a.lat);
//     ret.push_back(a.dislon);
//     ret.push_back(a.txalt);
//     //ret.push_back(a.loss);
//     return ret;
// }

// std::vector<std::vector<double>> Pathloss::getAllTxLoss(std::vector<double> points){
//     Coord closeRx;
//     Coord p;
//     Coord AntTx;
//     std::vector<std::vector<double>> arealoss;
//     std::vector<double> aux;
//     Pairtxrx ptrx;
//     double min_dkm = 99999;
//     double curr_dkm;

//     /*points vector to Coord type*/
//     p.assignCoord(points.at(0), points.at(1), points.at(2));
//     /*Distancia mas cercana al área*/
//     for(long unsigned int j = 0; j < this->varea.size(); j++){
//         curr_dkm = Distance(p.getStruct(), this->varea.at(j).getStruct());
//         if(curr_dkm < min_dkm){
//             min_dkm = curr_dkm;
//             closeRx = this->varea.at(j);
//         }
//     }  

//     for(auto it = vTx.begin(); it != vTx.end(); ++it){ //Por cada antena se calculan las pérdidas al área
//         p.assignCoord(it->at(0),it->at(1),it->at(2));
//         ptrx.setTx(p.getStruct());
//         ptrx.setRx(closeRx.getStruct());
//         ptrx.setLoss(this->freq, this->model, this->env_mode);
//         // aux.push_back(closeRx.getLat());
//         // aux.push_back(closeRx.getdisLon());
//         // aux.push_back(closeRx.getTxalt());
//         // aux.push_back(ptrx.getLoss());
//         // arealoss.push_back(aux);
//         it->push_back(ptrx.getLoss());
//         arealoss.push_back(*it);
//         aux.clear();
//     }
//     return arealoss;
// }