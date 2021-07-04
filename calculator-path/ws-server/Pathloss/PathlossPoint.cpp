
#include "PathlossPoint.hpp"

void PathlossPoint::onReady(std::vector<antenna> vantenna)
{
    for (auto &antenna : vantenna)
    {
        this->emisor->collectLoss(this->algorithm(this->corners.lat1, this->corners.lon1, 1 /* i + (j*amount_lat) */,
                                                  antenna.lat, antenna.lon, antenna.height, antenna.freq));
    }
    this->emisor->sendfflush();
    this->emisor->sendAll();
}

void PathlossPoint::calcPathloss(std::vector<antenna> &vantenna)
{
    this->emisor->reservePathloss(vantenna.capacity(), 1);
    this->algorithm = this->model->createAlgorithm([vantenna, this]()
                                                   { this->onReady(vantenna); });
    if (this->model->getModel() == pmodel::fspl || this->model->getModel() == pmodel::soil)
    {
        onReady(vantenna);
    }
}

std::vector<int> PathlossPoint::setgetDimensions(path corners, std::vector<double> resolution)
{
    return {};
}

nlohmann::json PathlossPoint::getParameters(std::vector<antenna> vantennas, std::vector<int> dimensions, ptAtributes atributes)
{
    //Crear JSON con los parámetros
    nlohmann::json j_out;
    j_out["parameters"] = {
        {"totalpoints", dimensions[0]},
        {"wlongitude", dimensions[0]},
        {"numantennas", vantennas.size()},
        {"progress", atributes.progress},
        {"corners", {{"topleft", {{"lat", atributes.corners.lat1}, {"lon", atributes.corners.lon1}}}, {"botright", {{"lat", atributes.corners.lat2}, {"lon", atributes.corners.lon2}}}}}};
    j_out["type"] = "dimensions";
    return j_out;
}