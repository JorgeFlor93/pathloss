#include <ixwebsocket/IXHttpClient.h>
#include <iostream>
#include "../ws-server/json.hpp"
#include <typeinfo>
#include <sstream>

using namespace ix;

template < typename Type > std::string to_str (const Type & t)
{
  std::ostringstream os;
  os << t;
  return os.str();
}

int main(){

  //
  // Preparation
  //
  HttpClient httpClient;
  HttpRequestArgsPtr args = httpClient.createRequest();

  args->connectTimeout = 60;
  args->transferTimeout = 60;
  args->followRedirects = true;
  args->maxRedirects = 10;
  args->verbose = true;
  args->compress = true;
  args->logger = [](const std::string& msg) { /* std::cout << msg; */ };
  args->onProgressCallback = [](int current, int total) -> bool {
      return true;
  };
  nlohmann::json input2;
  input2["locations"] = {};
  std::vector<std::vector<double>> vlatlon;
  std::vector<double> geoAntennaloc;
  geoAntennaloc.emplace_back(1.346);
  geoAntennaloc.emplace_back(43.156);
  vlatlon.emplace_back(geoAntennaloc);
  geoAntennaloc.clear();
  geoAntennaloc.emplace_back(1.346);
  geoAntennaloc.emplace_back(44.156);
  vlatlon.emplace_back(geoAntennaloc);
  for (std::vector<std::vector<double>>::const_iterator z = vlatlon.begin(); z != vlatlon.end(); ++z){
    int aux = 0;
    nlohmann::json j;
    for(std::vector<double>::const_iterator w = z->begin(); w != z->end(); ++w){
        if(aux == 0) j["longitude"] = *w;
        if(aux == 1) j["latitude"] = *w;
        aux++;
    }
    input2["locations"].push_back(j);
  } 
  HttpResponsePtr out;
  std::string url = "http://0.0.0.0:82/point-list-height";
  //
  // POST REQUEST
  //
  WebSocketHttpHeaders headers;
  headers["Content-Type"] = "application/json";
  headers["charset"] = "utf-8";
  args->extraHeaders = headers;
  out = httpClient.post(url, input2.dump(), args);
  //
  // RESULT
  //
  std::cout << "Payload: " << out->payload << "\n";
  nlohmann::json jparse = nlohmann::json::parse(out->payload);
  std::vector<float> heightsTx;
  for(std::size_t i = 0; i < vlatlon.size(); i++){
    heightsTx.emplace_back(jparse["response"][i]["data"]);
  }
  for (std::vector<float>::const_iterator w = heightsTx.begin(); w != heightsTx.end(); ++w){
    std::cout << *w << std::endl;
  }
  return 0;
}

// std::cout << "MsgError: " << out->errorMsg << std::endl;
// std::cout << "error: " << static_cast<int>(out->errorCode) << std::endl;