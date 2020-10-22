#pragma once
#include <string>
#include "../Communications/Websocket.hpp"
#include <ixwebsocket/IXWebSocketServer.h>

class Notificador{
public:
void setWSnotify(Websocket* ws);
void Notify(int progress, int total);
private:
Websocket* ws;
};