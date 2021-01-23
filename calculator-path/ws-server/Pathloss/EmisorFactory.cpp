
#include "EmisorFactory.hpp"

Emisor* EmisorFactory::createEmisor(Websocket* ws, int progress){
    Emisor* emisor = new Emisor(ws, progress);
    return emisor;
}