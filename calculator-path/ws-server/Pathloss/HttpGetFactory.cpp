
#include "HttpGetFactory.hpp";

HttpGet* HttpGetFactory::createHttpGet(path corners){
    HttpGet* httpget = new HttpGet{corners};
    return httpget;
}