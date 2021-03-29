
#include "HttpGet.hpp"

void HttpGet::setHeights(){
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
    // Synchronous Request  /* std::string url = "http://0.0.0.0:80/height-complete?top_lat=14.44502&top_lng=-3.567345&bot_lat=14.42832&bot_lng=-3.53973"; */
    //
    double toplat = this->corners.lat1;
    double toplon = this->corners.lon1;
    double botlat = this->corners.lat2;
    double botlon = this->corners.lon2;
    std::string toplatscheme ("top_lat=");
    std::string toplonscheme ("top_lng=");
    std::string botlatscheme ("bot_lat=");
    std::string botlonscheme ("bot_lng=");
    std::string secondlevel ("height-complete");
    std::string scheme ("http://");
    std::string hostname = "0.0.0.0:80";
    std::string url = scheme + hostname + "/" + secondlevel + "?" + 
                      toplatscheme + to_str(toplat) + "&" + toplonscheme + to_str(toplon) + "&" + 
                      botlatscheme + to_str(botlat) + "&" + botlonscheme + to_str(botlon);
    // GET request
    HttpResponsePtr out;
    out = httpClient.get(url, args);

    //
    // Result
    //
    auto payload = out->payload; // All the bytes from the response as an std::string
    nlohmann::json j_out = nlohmann::json::parse(payload);
    // std::cout << j_out["data"] << std::endl;
    // std::cout << j_out["data"][0] << std::endl;
    // std::cout << typeid(float((j_out["data"]))).name() << std::endl;
}

float HttpGet::getHeight(const int pos){
    return this->heights[pos];
}