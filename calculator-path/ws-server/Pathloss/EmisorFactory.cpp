
#include "EmisorFactory.hpp"

Emisor* EmisorFactory::createEmisor(Websocket* ws, int progress, std::vector<antenna> vantennas){
    Emisor* emisor = new Emisor(ws, progress, vantennas);
    return emisor;
}