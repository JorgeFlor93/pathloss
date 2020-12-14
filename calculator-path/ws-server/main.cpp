
#include <iostream>
#include "json.hpp"
#include <ixwebsocket/IXWebSocketServer.h>
#include "Executor/Executor.hpp"
#include "Communications/Websocket.hpp"
#include "common.h"

using namespace ix;

nlohmann::json sresult;
struct pathPath corner;
struct pathAtributes atributes;
std::vector<antenna> vAntennas;
double lat_res;
double lng_res;
std::function<double(const double lat, const double lon, const int pos, const double tlat, const double tlon, const float theight, const float frequency)> model;


int main (int argc, char** argv){

  WebSocketServer server{
    8080,        //SocketServer::kDefaultPort,
    "0.0.0.0",   //SocketServer::kDefaultHost,
    20,          //SocketServer::kDefaultTcpBacklog,
    1000,        //SocketServer::kDefaultMaxConnections,
    5,           //WebSocketServer::kDefaultHandShakeTimeoutSecs,
    SocketServer::kDefaultAddressFamily
  };

  server.setOnConnectionCallback( [&server] (std::shared_ptr<WebSocket> webSocket, std::shared_ptr<ConnectionState> connectionState) {
    webSocket->setOnMessageCallback( [webSocket, connectionState, &server] (const WebSocketMessagePtr msg) {
      if (msg->type == WebSocketMessageType::Message) {
        Executor executor;
        executor.setWebSocket(new Websocket(webSocket));
        executor.setActions(msg->str);
        executor.execute();
      }
    });
  });

  auto res = server.listen();
  if (!res.first) {
    return 1;
  }

  server.start();
  std::cout << "Started" << std::endl;
  server.wait();
}