
#include <iostream>
#include "json.hpp"
#include <ixwebsocket/IXWebSocketServer.h>
#include "Executor/Executor.hpp"
#include "Communications/Websocket.hpp"
#include "common.h"
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


void handler(int sig) {
  void *array[100];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 100);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

using namespace ix;

int main (int argc, char** argv){


  signal(SIGSEGV, handler);   // install our handler
  signal(SIGABRT, handler);
  
  WebSocketServer server{
    8080,        //SocketServer::kDefaultPort,
    "0.0.0.0",   //SocketServer::kDefaultHost,
    20,          //SocketServer::kDefaultTcpBacklog,
    1000,        //SocketServer::kDefaultMaxConnections,
    50,           //WebSocketServer::kDefaultHandShakeTimeoutSecs,
    SocketServer::kDefaultAddressFamily
  };
  server.enablePong();

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