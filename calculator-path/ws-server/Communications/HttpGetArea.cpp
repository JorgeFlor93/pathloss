
#include "HttpGetArea.hpp"
#include <iostream>

HttpGetArea::~HttpGetArea(){std::cout << "httpgetarea destruida" << std::endl;}

void HttpGetArea::decoder(HttpGet::OnReady onReady, const ix::HttpResponsePtr& response)
{
    // std::cout << "Body: " << response->payload << std::endl;
    std::cout << this->n << ":Response path heights:" << response->statusCode << std::endl;
    std::cout << this->n << ":error:" << static_cast<int>(response->errorCode) << std::endl;
    // std::cout << this->n << ":MsgError: " << response->errorMsg << std::endl;
    // std::cout << this->n << ":desc: " << response->description << std::endl;

    nlohmann::json j_out = nlohmann::json::parse(response->payload);
    // std::cout << "j_out1" << std::endl;
    // this->heights.reserve(sizeof(float) * j_out["image"]["width"].get<int>() * j_out["image"]["height"].get<int>());
    std::vector<float> reference (std::move(j_out["data"].get<std::vector<float>>())); 
    this->heights.reserve(sizeof(float) * reference.size());
    // std::cout << "reference size: " << reference.size() << std::endl;
    // std::cout << "this->heights size: " << this->heights.size() << std::endl;
    // std::cout << "j_out2" << std::endl;  
    this->heights.assign(reference.begin(), reference.end());
    // std::cout << "reference size: " << reference.size() << std::endl;
    // std::cout << "this->heights size: " << this->heights.size() << std::endl;

    onReady();
}

void HttpGetArea::request(HttpGet::OnReady onReady){
    //
    // Preparation
    //
    // Create URL  /* std::string url = "http://0.0.0.0:80/height-complete?top_lat=15.44502&top_lng=-3.567345&bot_lat=14.42832&bot_lng=-4.53973"; */
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
    std::string hostname ("genetic-server:80");
    std::string url = scheme + hostname + "/" + secondlevel + 
                      toplatscheme + to_str(toplat) + "&" + toplonscheme + to_str(toplon) + "&" + 
                      botlatscheme + to_str(botlat) + "&" + botlonscheme + to_str(botlon);
                      
    // static ix::HttpClient client(true);
    ix::HttpRequestArgsPtr args = this->client.createRequest(url, ix::HttpClient::kGet);
    this->configureArgs(args, this->n);
    bool ok = this->client.performRequest(args, [onReady, this](const ix::HttpResponsePtr& response){
        // std::cout << "pr" << std::endl;
        this->decoder(onReady, response);
    });
    std::cout << this->n << ":Request Path heights: " << ok << " [1=async|0=sync]" << std::endl;
    // for(int i = 0; i < 1000; i++){
    //     std::this_thread::sleep_for(std::chrono::milliseconds(5));
    // }
}

const std::vector<float>& HttpGetArea::get() const{
    return this->heights;
}
