# Websockets++

Websocket utilities to work with websockets in c++

## Installation

To install the utilities docker and docker-compose are needed.
There are no extra dependencies.

Run the following commandos from the root of the repository.

```bash
docker-compose build   # BUILD THE IMAGES
docker-compose up      # LAUNCH THE CONTAINERS
```

## Components

Five containers will be launched, three of them uses external ports (80, 8080 and 8081) that can be changed on the docker-compose.yml file.
From those containers one is just a demo/tests so it will die leaving just four containers running.

### ws-web **(PORT 80)**

Webpage to make ws connections. The webpage was build using React.

* Access the webpage over [http://0.0.0.0:80/](http://0.0.0.0:80/)
* Connect to the ws-server(8080) or ws-server-node(8081) containers by changing the PORT field.
* Send data to the websocket servers running on them.
  Whatever is returned by the server will be displayed on the web (just the last message)
  The servers are just echo servers so whatever is sent will be outputted on the as well as on the terminal where docker-compose up was run.

### ws-client

Websocket client written in cpp that uses [IXWebSocket](https://github.com/machinezone/IXWebSocket) library.
This container will run at start and send 20 messages to the ws-server.
Then it will shut down without waiting for the responses to received.
This is just a demo of a cpp client ws implementation as well as a test for within docker ws connection to the ws-server.

### ws-server **(PORT 8080)**

Websocket server written in cpp that uses [IXWebSocket](https://github.com/machinezone/IXWebSocket) library.
It also uses [nlohmann/json](https://github.com/nlohmann/json) library to parse received data.
The server can be accessed though ws://0.0.0.0:8080/ externally and from ws://ws-server:8080/ from within docker.

The server is an echo server that will return whatever it received as long as it is json formatted.
It will also print the received data on the terminal where docker-compose up was run.


