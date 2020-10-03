
#include "area.hpp"

void cArea::setArea(std::vector<double> tl, std::vector<double> br){
    this->varea = get_area(tl[0], tl[1], br[0], br[1], tl[2]/*or br[2]*/);
}

std::vector<Coord> cArea::getArea(){
    return this->varea;
}