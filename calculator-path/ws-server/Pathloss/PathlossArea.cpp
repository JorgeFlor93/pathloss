#include "PathlossArea.hpp"
#include <iostream>
#include <math.h>

void PathlossArea::onReady(std::vector<antenna> vantenna)
{
    std::cout << this->n << ":Start Calculus" << std::endl;
    double start_point_lat = this->corners.lat1 - this->resolution[0] / 2;
    double current_point_lat = start_point_lat;
    double current_point_lon = this->corners.lon1 + this->resolution[1] / 2;
    double start_point_lon = current_point_lon;
    for (int j = 0; j < dimensions[1]; j++)
    {
        for (int i = 0; i < dimensions[0]; i++)
        {
            double bestloss;
            for (auto &antenna : vantenna)
            {
                /*CALCULO DE LA PERDIDA*/
                double loss;
                // std::cout << "lat:" << antenna.lat << ", lon: " << antenna.lon << std::endl;
                loss = this->algorithm(current_point_lat, current_point_lon, i + (j * dimensions[0]),
                                       antenna.lat, antenna.lon, antenna.height, antenna.freq);
                if (antenna.id == "1")
                    bestloss = loss;
                else if (loss <= bestloss)
                    bestloss = loss;
            }
            this->emisor->collectLoss(bestloss);
            current_point_lon += this->resolution[0];
        }
        current_point_lon = start_point_lon;
        current_point_lat -= this->resolution[1];
    }
    // std::cout << "onready" << std::endl;
    this->emisor->sendfflush();
    //
    // SEND ALL COLLECT
    //
    this->emisor->sendAll();
}

void PathlossArea::calcPathloss(std::vector<antenna> &vantenna)
{
    this->emisor->reservePathloss(this->dimensions[1], this->dimensions[0]);
    // std::cout << "calcpath" << std::endl;
    this->algorithm = this->model->createAlgorithm([vantenna, this]()
                                                   { this->onReady(vantenna); });
    if (this->model->getModel() == pmodel::fspl || this->model->getModel() == pmodel::soil)
    {
        onReady(vantenna);
    }
}

std::vector<int> PathlossArea::setgetDimensions(path corners, std::vector<double> resolution)
{
    double inc_lng = abs(corners.lon1 - corners.lon2);
    double width = round(inc_lng / resolution[1]);

    double inc_lat = abs(corners.lat1 - corners.lat2);
    double height = round(inc_lat / resolution[0]);

    std::vector<int> dimensions;
    dimensions.emplace_back(width);
    dimensions.emplace_back(height);
    this->dimensions = dimensions;
    return dimensions;
}

nlohmann::json PathlossArea::getParameters(std::vector<antenna> vantennas, std::vector<int> dimensions, ptAtributes atributes)
{
    //Crear JSON con los parámetros
    nlohmann::json j_out;
    j_out = {
        {"model", this->model->getModelName()},
        {"totalpoints", dimensions[0] * dimensions[1]},
        {"height", dimensions[1]},
        {"width", dimensions[0]},
        {"numantennas", vantennas.size()},
        {"progress", atributes.progress},
        {"corners", {{"topleft", {{"lat", atributes.corners.lat1}, {"lon", atributes.corners.lon1}}}, {"botright", {{"lat", atributes.corners.lat2}, {"lon", atributes.corners.lon2}}}}}};
    return j_out;
}