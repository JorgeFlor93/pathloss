
#include "EmisorFactory.hpp"

Emisor* EmisorFactory::createEmisor(Websocket* ws, int progress, std::vector<antenna> vantennas, path corners){
    Emisor* emisor = new Emisor(ws, progress, vantennas, corners);
    return emisor;
}