
#pragma once
#include "../common.h"
#include <string>
#include <vector> 
#include <ixwebsocket/IXHttpClient.h>
#include "../json.hpp"
#include <typeinfo>
#include <sstream>

using namespace ix;

class HttpGet{
    public:
    HttpGet(path corners) : corners(corners){}; 
    void setHeights();
    float getHeight(const int pos);
    private:
    path corners;
    std::vector<float> heights;
};

template < typename Type > std::string to_str (const Type & t)
{
  std::ostringstream os;
  os << t;
  return os.str ();
}