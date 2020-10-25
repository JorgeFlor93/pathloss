
#include "distance.hh"

double lat_res;
double lng_res;

double miles_to_km(const double miles){   
    return miles*1.60934;
}

double pDistance(const double tlat, const double tlon, const double lat, const double lon)
{

	double lat1, lon1, lat2, lon2, distance;

	lat1 = tlat * DEG2RAD;
	lon1 = tlon * DEG2RAD;
	lat2 = lat * DEG2RAD;
	lon2 = lon * DEG2RAD;

	distance =
	    3959.0 * acos(sin(lat1) * sin(lat2) +
			  cos(lat1) * cos(lat2) * cos((lon1) - (lon2)));

	distance = miles_to_km(distance);
	return distance;
}

void Distance::set_res(std::string resolution){

/* Resolution (point-to-point distance) 
* 0.00208333333 -> 225m
* 0.0002777778 -> 30m (1 arcsec)
* 0.000458333 -> 50m
* 0.000808333 -> 90m (3 arcsec)
*/
    if(resolution == "90m"){
        lat_res = 0.000808333;
        lng_res = 0.000808333;
    }
    else if(resolution == "30m"){
        lat_res = 0.0002777778;
        lng_res = 0.0002777778;
    }
}

int get_dimension_lng(const double line_start_lng, const double line_end_lng){
    double inc_lng = 0.0;

    inc_lng = abs(line_start_lng - line_end_lng);

    return round(inc_lng/lng_res);
}

int get_dimension_lat(const double line_start_lat, const double line_end_lat){
    double inc_lat = 0.0;

    inc_lat = abs(line_start_lat - line_end_lat);

    return round(inc_lat/lat_res);
}

int Distance::getTotalpoints(const double tl_lat, const double tl_lon, const double br_lat, const double br_lon){
    return (get_dimension_lat(tl_lat, br_lat) * get_dimension_lng(tl_lon, br_lon)); // amount_lat * amount_lng;
}

std::vector<double> Distance::get_arealoss(const double top_lat , const double top_lng, const double bot_lat, const double bot_lng, 
                                        const double tlat, const double tlon, const float theight, const float frequency,
                                        std::function<double(const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)> getLoss)
{
    int amount_lat = get_dimension_lat(top_lat, bot_lat);
    int amount_lng = get_dimension_lng(top_lng, bot_lng);
    int total_points = amount_lat * amount_lng;
    double loss = 0;
    std::vector<double> pathloss;
    pathloss.reserve(sizeof(double)*total_points);
    double start_point_lat = top_lat - lat_res/2;
    double current_point_lat = start_point_lat;
    double current_point_lon = top_lng + lng_res/2;

    for(int i = 0; i < amount_lng; i++){
        for(int j = 0; j < amount_lat; j++){
            
            /*CALCULO DE LA PERDIDA*/
            loss = getLoss(current_point_lat, current_point_lon, i + (j*amount_lat), tlat, tlon, theight, frequency);
            
            pathloss.emplace_back(loss);
            
            current_point_lat -= lat_res;
        }
        current_point_lat = start_point_lat;
       current_point_lon += lng_res;
    }
    return pathloss;
}

double calcHata(const double lat,const double lon, const float height, const double tlat, const double tlon, const float theight, const float frequency, const int tipo_terreno){
    return HATApathLoss(frequency, theight, height, pDistance(tlat, tlon, lat, lon), tipo_terreno);
}
double calcFSPL(const double lat,const double lon, const double tlat, const double tlon, const float theight, const float frequency){
   return FSPLpathLoss(frequency, pDistance(tlat, tlon, lat, lon));
}

// std::vector<double> get_line(double line_start_lat , double line_start_lng, double line_end_lat, double line_end_lng){

//     int end = 0;
//     double module = 0.0;
//  // Matrix(type, rows, col)
//     double start_point_lat = line_start_lat;
//     double start_point_lon = line_start_lng;

//     double end_point_lat = line_end_lat;
//     double end_point_lon = line_end_lng;

//     double full_vector_lat =  line_end_lat - line_start_lat; 
//     double full_vector_lon =  line_end_lng -line_start_lng; 

//     module = full_vector_lat * full_vector_lat + full_vector_lon * full_vector_lon;

//     double res_vector_lat = lat_res;
//     double res_vector_lon = lng_res;

//     double unit_vector_lat = (full_vector_lat / module) * lat_res;
//     double unit_vector_lon = (full_vector_lon / module) * lng_res;

//     double current_point_lat = start_point_lat;
//     double current_point_lon = start_point_lon;

//     end = round((module)/(lat_res));

//     std::vector<double> point_list;
//     point_list.reserve(sizeof(double)*end);
//     point_list.push_back(current_point);

//     for(int i=0;i<end;i++){
//         current_point = current_point + unit_vector;
//         point_list.push_back(current_point);
//     }
    
//    return point_list;
// }