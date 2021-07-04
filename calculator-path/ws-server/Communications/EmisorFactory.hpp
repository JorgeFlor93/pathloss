#pragma once
#include <vector>
#include "Emisor.hpp"
#include "../common.h"
#include "Websocket.hpp"


class EmisorFactory{
    public:
    Emisor* createEmisor(Websocket* ws, int progress, std::vector<antenna> vantennas, path corners, int n);
};