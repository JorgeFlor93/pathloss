#include "PathlossArea.hpp"

std::vector<double> PathlossArea::calcPathloss(const double tlat, const double tlon, const float theight, const float frequency)
{
    int amount_lat = getDimensionLat(corner.lat1, corner.lat2);
    int amount_lng = getDimensionLng(corner.lon1, corner.lon2);
    int total_points = amount_lat * amount_lng;
    std::vector<double> pathlossarea;
    pathlossarea.reserve(sizeof(double)*total_points);   
    double start_point_lat = corner.lat1 - lat_res/2;
    double current_point_lat = start_point_lat;
    double current_point_lon = corner.lon1 + lng_res/2;
    double loss = 0;
    for(int i = 0; i < amount_lng; i++){
        for(int j = 0; j < amount_lat; j++){                      
            
            /*CALCULO DE LA PERDIDA*/
            loss = model(current_point_lat, current_point_lon, 1/* i + (j*amount_lat) */, tlat, tlon, theight, frequency);
            
            pathlossarea.emplace_back(loss);
            current_point_lat -= lat_res;
        }
        current_point_lat = start_point_lat;
       current_point_lon += lng_res;
    }
    return pathlossarea;
}

void PathlossArea::send(std::vector<double> loss){}

int getDimensionLng(double line_start_lng, double line_end_lng){
    double inc_lng = abs(line_start_lng - line_end_lng);
    return round(inc_lng/lng_res);
}

int getDimensionLat(double line_start_lat, double line_end_lat){
    double inc_lat = abs(line_start_lat - line_end_lat);    
    return round(inc_lat/lat_res);
}

// int PathlossArea::getTotalpoints(const double tl_lat, const double tl_lon, const double br_lat, const double br_lon){
//     return (getDimensionLat(tl_lat, br_lat) * getDimensionLng(tl_lon, br_lon)); // amount_lat * amount_lng;
// }