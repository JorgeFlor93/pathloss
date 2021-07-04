
#include "EmisorFactory.hpp"
#include <iostream>
Emisor* EmisorFactory::createEmisor(Websocket* ws, int progress, std::vector<antenna> vantennas, path corners, int n){
    std::cout << n << ":Create Emisor object" << std::endl;  
    Emisor* emisor = new Emisor(ws, progress, vantennas, corners, n);
    return emisor;
}