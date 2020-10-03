#include <iostream>
#include <vector>
#include "coordinate.hpp"
#include "distance.hh"
#include "../json.hpp"

class cArea{
public:
void setArea(std::vector<double> tl, std::vector<double> br);
std::vector<Coord> getArea();
private:
std::vector<Coord> varea;
};