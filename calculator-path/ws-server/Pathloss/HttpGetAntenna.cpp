
#include "HttpGetAntenna.hpp"
#include <ixwebsocket/IXHttpClient.h>
#include <iostream>

void HttpGetAntenna::request(HttpGet::OnReady onReady){
    //
    // Preparation
    // 
    nlohmann::json input;
    input["locations"] = {};
    for (std::vector<std::vector<double>>::const_iterator z = this->vlatlon.begin(); z != this->vlatlon.end(); ++z){
        int aux = 0;
        nlohmann::json j;
        for(std::vector<double>::const_iterator w = z->begin(); w != z->end(); ++w){
                if(aux == 0) j["longitude"] = *w;
                if(aux == 1) j["latitude"] = *w;
                aux++;
        }
        input["locations"].push_back(j);
    } 
    std::cout << input.dump(4) << "\n";
    std::string url = "http://genetic-server:80/point-list-height";

    ix::HttpRequestArgsPtr args = this->client.createRequest(url, ix::HttpClient::kPost);
    std::cout << "tx1" << std::endl;
    this->configureArgs(args);
    std::cout << "tx2" << std::endl;
    args->body = input.dump();
    std::cout << "tx3" << std::endl;
    bool ok = this->client.performRequest(args, [onReady, this](const ix::HttpResponsePtr& response){
        std::cout << "statuscode: " << response->statusCode << std::endl;
        std::cout << "payload: " <<response->payload << std::endl;
        nlohmann::json j_out = nlohmann::json::parse(response->payload);
        for(std::size_t i = 0; i < vlatlon.size(); i++){
            this->heightsTx.emplace_back(j_out["response"][i]["data"].get<float>());
        }
        onReady();
    });
    std::cout << "Ok Antenna:" << ok << std::endl;
    for(int i = 0; i < 1000; i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

const std::vector<float>& HttpGetAntenna::get() const{
    return this->heightsTx;
}