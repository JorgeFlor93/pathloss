#ifndef _COMMON_H_
#define _COMMON_H_

#include <vector>
#include <string>
#include "json.hpp"
#include <functional>

#define	KM_PER_MILE	1.609344
#define	METERS_PER_MILE 1609.344
#define DEG2RAD	1.74532925199e-02


enum class ptype {
    Area,
    Line,
    Point
};

enum class pmodel{
    fspl,
    hata,
    egli
};

enum class penv{
    urban,
    suburban,
    rural
};

struct path{ // Line or Area(corners or start-end points)
    double lat1;
    double lon1;
    double lat2;
    double lon2;
};

struct ptAtributes {
    //std::string propagationModel;
    pmodel propagationmodel;
    penv propagationEnvironment;
    ptype enumtype; 
    std::vector<double> resolution;
    int progress;
    nlohmann::json edges; // Area Corners, Line points start-end, or Point position
    path corners;
};

struct antenna{
    std::string id;
    double lat;
    double lon;
    float height;
    float freq;
};

#endif /* _COMMON_H_ */