#include <ixwebsocket/IXHttpClient.h>
#include <iostream>
#include "../ws-server/json.hpp"
#include <typeinfo>
#include <sstream>
#include <chrono>
#include <thread>

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
  
  nlohmann::json input2;
  input2["locations"] = {};
  // for (int i = 0; i < 3; i++){
  //   nlohmann::json j;
  //   j["longitude"] = 1.346;
  //   j["latitude"] = 43.156;
  //   input2["locations"].push_back(j);
  // }
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
  // HttpResponsePtr out;
  std::string url = "http://0.0.0.0:82/point-list-height";
  //
  // POST REQUEST
  //
  WebSocketHttpHeaders headers;
  headers["Content-Type"] = "application/json";
  headers["charset"] = "utf-8";
  HttpClient httpClient(true);
  HttpRequestArgsPtr args = httpClient.createRequest( url, ix::HttpClient::kPost);
  args->body = input2.dump();
  args->extraHeaders = headers;
  args->connectTimeout = 60;
  args->transferTimeout = 60;
  args->followRedirects = true;
  args->maxRedirects = 10;
  args->verbose = true;
  args->compress = true;
  args->logger = [](const std::string& msg) { std::cout << msg << std::endl; };
  args->onProgressCallback = [](int current, int total) -> bool {
      return true;
  };
  std::cout << "Request..." << std::endl;
  bool ok = httpClient.performRequest(args, [](const HttpResponsePtr& response)
    {
        // This callback execute in a background thread. Make sure you uses appropriate protection such as mutex
        auto statusCode = response->statusCode; // acess results
        std::cout << "Payload: " << response->payload << "\n";
        std::cout << statusCode << std::endl;

    }
  );
  std::this_thread::sleep_for(std::chrono::seconds(3));
  std::cout << "ok " << ok << std::endl;

  // out = httpClient.post(url, input2.dump(), args);
  //
  // RESULT
  //
  // std::cout << "Payload: " << out->payload << "\n";
  // nlohmann::json jparse = nlohmann::json::parse(out->payload);
  // std::vector<float> heightsTx;
  // for(int i = 0; i < vlatlon.size(); i++){
  //   heightsTx.emplace_back(jparse["response"][i]["data"]);
  // }
  // for (std::vector<float>::const_iterator w = heightsTx.begin(); w != heightsTx.end(); ++w){
  //   std::cout << *w << std::endl;
  // }
  return 0;
}

// std::cout << "MsgError: " << out->errorMsg << std::endl;
// std::cout << "error: " << static_cast<int>(out->errorCode) << std::endl;