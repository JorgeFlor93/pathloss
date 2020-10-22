#include "Pathloss.hpp"

void Pathloss::setAtributes(nlohmann::json atributes)
{   
    this->propagationMethod = atributes["propagationMethod"].get<std::string>();
    this->propagationModel = atributes["propagation_mode"].get<std::string>();
    this->resolution = atributes["resolution"].get<std::string>();
    this->location = atributes["location"][0].get<nlohmann::json>();
    this->progress = atributes["progress"].get<int>();
 
    for(nlohmann::json& it : atributes["antennas"])
    {
        this->vectorTx.emplace_back(Antenna{
                                    (it)["lat"].get<double>(), 
                                    (it)["lon"].get<double>(), 
                                    (it)["height"].get<float>(),
                                    (it)["type"].get<std::string>(),
                                    (it)["id"].get<std::string>(),
                                    (it)["frequency"].get<float>()
                                });
    }
}

nlohmann::json Pathloss::setAreaLoss(){
// std::vecctor<double> height = servidor.pedir();
// std::vector<double> tipo_terreno;
// std::function<double (const double lat, const double lng, const int pos) accion;
// switch (algoritmo)
// {
// case HATA:
// accion = [height,tipo_terreno](const double lat, const double lng, const int pos)
// {
//     calcularPerdida(lat, lng,height[pos], tipo_terreno[pos])
// };
// case EIBERT_KULMAN:
// accion = [height](constdouble lat, const double lng, const int pos){
// calcularPerdida2(lat, lng, height[pos],)
// };
// }
// get_arealoss(..., );
// }
    distance d;
    int area_points = 0;
    std::vector<double> propagation;
    nlohmann::json jout;
    std::vector<double> tl = this->location["topleft"].get<std::vector<double>>();
    std::vector<double> br = this->location["botright"].get<std::vector<double>>();
    d.set_res(this->resolution); // Input Resolution (30m, 90m)
    area_points = d.getTotalpoints(tl, br); // TotalPoints
    
    for(Antenna& itx : this->vectorTx){   
        propagation = d.get_arealoss(tl[0], tl[1], br[0], br[1], //Area Corners
                                    itx.getStruct(), itx.getFrequency(), //struct site tx(lat, lon), freq tx
                                    this->propagationMethod, 
                                    this->propagationModel,
                                    this->progress);           
        jout.emplace_back(nlohmann::json::array({"antenna", {
                        {"id", itx.getId()}, 
                        {"type", itx.getType()},
                        {"lat", itx.getLat()},
                        {"lon", itx.getLon()},
                        {"height", itx.getHeight()},
                        {"frequency", itx.getFrequency()},
                        {"Area points", area_points},
                        {"Area Loss", propagation}}
                    }));     
    }
    return jout;
}

// void Pathloss::setArea(std::vector<double> tl, std::vector<double> br){
//     this->varea = get_area(tl[0], tl[1], br[0], br[1], 1/*Altura del receptor*/);
// }

// std::vector<Coord> Pathloss::getArea(){
//     return this->varea;
// }
// std::vector<std::vector<double>> Pathloss::getvectorArea(){ //Conversor std::vector<Coord> TO std::vector<std::vector<double>>
//     std::vector<std::vector<double>> vector;
//     std::vector<double> coord;
//     for (std::vector<Coord>::iterator it = this->varea.begin(); it != this->varea.end(); ++it){
//         coord.push_back(it->getLat());
//         coord.push_back(it->getdisLon());
//         coord.push_back(it->getTxalt());
//         vector.push_back(coord);
//         coord.clear();
//     }
//     return vector;
// } shared_ptr<Photo> temp = dynamic_pointer_cast<Photo>(p);	

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