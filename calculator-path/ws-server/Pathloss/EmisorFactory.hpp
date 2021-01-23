#pragma once
#include <vector>
#include "Emisor.hpp"
#include "../Communications/Websocket.hpp"


class EmisorFactory{
    public:
    Emisor* createEmisor(Websocket* ws, int progress);
};