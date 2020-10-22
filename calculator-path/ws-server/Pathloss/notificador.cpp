#include "notificador.hpp"

void Notificador::setWSnotify(Websocket* ws) {
  this->ws = ws;
}

void Notificador::Notify(int progress, int total){
    this->ws->sendNotification(progress,total);
}
