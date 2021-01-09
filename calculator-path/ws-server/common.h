#ifndef _COMMON_H_
#define _COMMON_H_

#include <vector>
#include <string>
#include "json.hpp"
#include <functional>

#define	KM_PER_MILE	1.609344
#define DEG2RAD		1.74532925199e-02

struct ptAtributes {
	float freq;
    std::string propagationModel;
    int propagationEnv;
    std::string resolution;
    std::string type; // Area, Line, Point
    nlohmann::json edges; // Area Corners, Line points start-end, or Point position
    int progress;
};

struct antenna{
    double lat;
    double lon;
    float height;
    std::string id;
    float freq;
    /* antenna(double lat, double lon, float height, std::string id, float freq) : lat(lat), lon(lon), height(height), id(id), freq(freq){} */
};

struct path{ // Line or Area(corners or start-end points)
    double lat1;
    double lon1;
    double lat2;
    double lon2;
};

extern nlohmann::json sresult;
extern double lat_res; /* resolution */
extern double lng_res;
extern ptAtributes atributes;
extern std::vector<antenna> vAntennas; 
extern path corner; //Area corners, start-end line, point position
extern std::function<double(const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)> model;

#endif /* _COMMON_H_ */