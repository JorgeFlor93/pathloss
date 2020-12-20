#include "PathlossArea.hpp"

std::vector<double> PathlossArea::calcPathloss(){
    std::vector<double> loss;
    for(antenna& it : vAntennas){
         loss = areaPathloss(corner.lat1, corner.lon1, corner.lat2, corner.lon2, it.lat, it.lon, it.height, it.freq, model, 0);
    }
    return loss;
}

std::vector<double> PathlossArea::areaPathloss(const double top_lat , const double top_lng, const double bot_lat, const double bot_lng, 
                                        const double tlat, const double tlon, const float theight, const float frequency,
                                        std::function<double(const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)> alg,
                                        int progress)
{
    int amount_lat = getDimensionLat(top_lat, bot_lat);
    int amount_lng = getDimensionLng(top_lng, bot_lng);
    int total_points = amount_lat * amount_lng;
    std::vector<double> pathlossarea;
    pathlossarea.reserve(sizeof(double)*total_points);
    double start_point_lat = top_lat - lat_res/2;
    double current_point_lat = start_point_lat;
    double current_point_lon = top_lng + lng_res/2;

    int c = 0; //contador de iteraciones
    double loss = 0;

    for(int i = 0; i < amount_lng; i++){
        for(int j = 0; j < amount_lat; j++){
                       
            /*CALCULO DE LA PERDIDA*/
            loss = i + j * amount_lat;/* alg(current_point_lat, current_point_lon, i + (j*amount_lat), tlat, tlon, theight, frequency); */
            
            pathlossarea.emplace_back(loss);
            
            current_point_lat -= lat_res;
            ++c;
        }
        current_point_lat = start_point_lat;
       current_point_lon += lng_res;
    }

    return pathlossarea;
}

void PathlossArea::send(std::vector<double> loss){}

int getDimensionLng(const double line_start_lng, const double line_end_lng){
    double inc_lng = 0.0;

    inc_lng = abs(line_start_lng - line_end_lng);

    return round(inc_lng/lng_res);
}

int getDimensionLat(const double line_start_lat, const double line_end_lat){
    double inc_lat = 0.0;

    inc_lat = abs(line_start_lat - line_end_lat);

    return round(inc_lat/lat_res);
}

// int PathlossArea::getTotalpoints(const double tl_lat, const double tl_lon, const double br_lat, const double br_lon){
//     return (getDimensionLat(tl_lat, br_lat) * getDimensionLng(tl_lon, br_lon)); // amount_lat * amount_lng;
// }