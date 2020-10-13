
#include "distance.hh"

/* Resolution (point-to-point distance) 
* 0.00208333333 -> 225m
* 0.0002777778 -> 30m (1 arcsec)
* 0.000458333 -> 50m
* 0.000808333 -> 90m (3 arcsec)
*/

double lat_res = 0.000808333;
double lng_res = 0.000808333;

std::vector<Eigen::Matrix<double, 1, 2>> get_line(double line_start_lat , double line_start_lng, double line_end_lat, double line_end_lng){

    int end = 0;
    double module = 0.0;

    Eigen::Matrix<double, 1, 2> start_point; // Matrix(type, rows, col)
    start_point(0,0) = line_start_lat;
    start_point(0,1) = line_start_lng;

    Eigen::Matrix<double, 1, 2> end_point;
    end_point(0,0) = line_end_lat;
    end_point(0,1) = line_end_lng;

    Eigen::Matrix<double, 1, 2> full_vector;
    full_vector (0, 0) =  line_end_lat - line_start_lat; 
    full_vector (0, 1) =  line_end_lng -line_start_lng; 

    module = full_vector.norm();

    Eigen::Matrix<double, 1, 2> res_vector;
    res_vector(0,0) = lat_res;
    res_vector(0,1) = lng_res;


    Eigen::Matrix<double, 1, 2> unit_vector;
    unit_vector(0,0) = (full_vector(0,0) / module) * lat_res;
    unit_vector(0,1) = (full_vector(0,1) / module) * lng_res;

    Eigen::Matrix<double, 1, 2> current_point = start_point;

    end = round((module)/(lat_res));

    std::vector<Eigen::Matrix<double, 1, 2>> point_list;
    point_list.push_back(current_point);

    for(int i=0;i<end;i++){
        current_point = current_point + unit_vector;
        point_list.push_back(current_point);
    }
    
   return point_list;
}

int get_dimension_lng(double line_start_lng, double line_end_lng){
    double inc_lng = 0.0;

    inc_lng = abs(line_start_lng - line_end_lng);

    return round(inc_lng/lng_res);
}

int get_dimension_lat(double line_start_lat, double line_end_lat){
    double inc_lat = 0.0;

    inc_lat = abs(line_start_lat - line_end_lat);

    return round(inc_lat/lat_res);
}

std::vector<Coord> get_area(double top_lat , double top_lng, double bot_lat, double bot_lng, float Height){
    
    //get lat and lng dimension
    int amount_lat = 0;
    int amount_lng = 0;
    amount_lat = get_dimension_lat(top_lat, bot_lat);
    amount_lng = get_dimension_lng(top_lng, bot_lng);

    std::vector<Coord> varea;
    varea.reserve(amount_lat*amount_lng);
    Coord p;
    std::vector<double> start_point;
    std::vector<double> current_point;

    start_point.emplace_back(top_lat - lat_res/2);
    current_point.emplace_back(start_point.at(0));
    current_point.emplace_back(top_lng + lng_res/2);

    for(int i = 0; i < amount_lng; i++){
        for(int j = 0; j < amount_lat; j++){
            if(current_point.at(1) >= 180 && current_point.at(1) < 360){
                current_point.at(1) = 360 - current_point.at(1);
                current_point.at(1) *= -1;
            }
            else if(current_point.at(1) > 0 && current_point.at(1) < 180){
                current_point.at(1) *= -1;
            }
            
            p.assignCoord(current_point.at(0), current_point.at(1), 1);
            //p.setAlt();
            varea.emplace_back(p);
            current_point.at(0) -= lat_res;
        }
        current_point.at(0) = current_point.at(0);
       current_point.at(1) += lng_res;
    }
    current_point.shrink_to_fit();
    start_point.shrink_to_fit();
    // varea.shrink_to_fit();
    return varea;
}
