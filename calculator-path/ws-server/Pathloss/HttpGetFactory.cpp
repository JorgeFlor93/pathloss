
#include "HttpGetFactory.hpp"

HttpGet* HttpGetFactory::createHttpGet(path corners, Websocket* ws){
    HttpGet* httpget = new HttpGet{corners, ws};
    return httpget;
}