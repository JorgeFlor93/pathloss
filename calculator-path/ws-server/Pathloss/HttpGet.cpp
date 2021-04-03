
#include "HttpGet.hpp"

void HttpGet::setHeights(){

    // nlohmann::json d;
    // d["result"] = "Hello";
    // this->ws->sendPartial(d);
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
    // Synchronous Request  /* std::string url = "http://0.0.0.0:80/height-complete?top_lat=15.44502&top_lng=-3.567345&bot_lat=14.42832&bot_lng=-4.53973"; */
    //
    double toplat = this->corners.lat1;
    double toplon = this->corners.lon1;
    double botlat = this->corners.lat2;
    double botlon = this->corners.lon2;
    std::string toplatscheme ("top_lat=");
    std::string toplonscheme ("top_lng=");
    std::string botlatscheme ("bot_lat=");
    std::string botlonscheme ("bot_lng=");
    std::string secondlevel ("height-complete?");
    std::string scheme ("http://");
    std::string hostname = "0.0.0.0:82";
    std::string url = scheme + hostname + "/" + secondlevel + 
                      toplatscheme + to_str(toplat) + "&" + toplonscheme + to_str(toplon) + "&" + 
                      botlatscheme + to_str(botlat) + "&" + botlonscheme + to_str(botlon);
    
    nlohmann::json d3;
    d3["payload"] = url;
    this->ws->sendPartial(d3);
    // GET request
    HttpResponsePtr out;
    out = httpClient.get(url, args);
    std::this_thread::sleep_for(std::chrono::milliseconds(20000));
    //
    // Result
    //
    auto payload = out->payload; // All the bytes from the response as an std::string
    nlohmann::json d2;
    d2["payload"] = payload;
    this->ws->sendPartial(d2);
    // nlohmann::json j_out = nlohmann::json::parse(payload);
    // nlohmann::json data;
    // data["result"] = j_out["data"].get<std::vector<float>>();
    // data["result"] = j_out["image"]["width"].get<int>();
    // this->ws->sendPartial(j_out);
    // this->heights.reserve(sizeof(float) * j_out["image"]["width"].get<int>() * j_out["image"]["height"].get<int>());
    // this->heights = j_out["data"].get<std::vector<float>>();
}

float HttpGet::getHeight(const int pos){
    return this->heights[pos];
}