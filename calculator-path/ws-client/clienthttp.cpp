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
  return os.str ();
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
    // std::cerr << "\r"
    //             << "Downloaded " << current << " bytes out of " << total;
    return true;
};
//
// Synchronous Request
//
HttpResponsePtr out;
std::string url = "http://0.0.0.0:82/height-complete?top_lat=51.8&top_lng=10.5&bot_lat=51&bot_lng=11.3";

// double toplat = 51.8;
//     double toplon = 10.5;
//     double botlat = 51;
//     double botlon = 9.7;
//     std::string toplatscheme ("top_lat=");
//     std::string toplonscheme ("top_lng=");
//     std::string botlatscheme ("bot_lat=");
//     std::string botlonscheme ("bot_lng=");
//     std::string secondlevel ("height-complete?");
//     std::string scheme ("http://");
//     std::string hostname = "0.0.0.0:80";
//     std::string url = scheme + hostname + "/" + secondlevel + 
//                       toplatscheme + to_str(toplat) + "&" + toplonscheme + to_str(toplon) + "&" + 
//                       botlatscheme + to_str(botlat) + "&" + botlonscheme + to_str(botlon);

// // GET request
out = httpClient.get(url, args);

//
// Result
//
auto payload = out->payload; // All the bytes from the response as an std::string
std::cout << "payload: " << payload << std::endl;
nlohmann::json j_out = nlohmann::json::parse(payload);
// std::cout << typeid(j_out["data"].get<std::vector<float>>()).name() << std::endl;
std::vector<float> heights; 
heights.reserve(sizeof(float) * j_out["image"]["width"].get<int>() * j_out["image"]["height"].get<int>());
for(int i = 0; i < int(j_out["image"]["width"]) * int(j_out["image"]["height"]); i++){
  heights.emplace_back(j_out["data"][i].get<float>());
}
// heights = j_out["data"].get<std::vector<float>>();
// std::cout << j_out["data"] << std::endl;
for(int i = 0; i < int(j_out["image"]["width"]) * int(j_out["image"]["height"]); i++){
// std::cout << heights[i] << ", ";
}
std::cout << "\n";
std::cout << heights[0]  << "," << heights[1] << ", " << heights[2]  << "," << heights[3] <<", " << heights[4]  << "," << heights[5] << std::endl;
std::cout << "Size: " << heights.size() << "\n";
std::cout << "total_points: " << j_out["image"]["width"].get<int>() * j_out["image"]["height"].get<int>() << "\n"; 
std::cout << typeid(heights[0]).name() << std::endl;
// std::cout << j_out["data"][0] << std::endl;
// std::cout << typeid(float((j_out["data"]))).name() << std::endl;
return 0;
}
