
#include "HttpGetAbs.hpp"
#include <iostream>

void HttpGetAbs::configureArgs(ix::HttpRequestArgsPtr& args, int n){
    ix::WebSocketHttpHeaders headers;
    headers["Content-Type"] = "application/json";
    headers["charset"] = "utf-8";
    args->extraHeaders = headers;
    args->connectTimeout = 60;
    args->transferTimeout = 60;
    args->followRedirects = true;
    args->maxRedirects = 10;
    args->verbose = true;
    args->compress = true;
    args->logger = [](const std::string& msg) { /* std::cout << msg << std::endl; */ };
    // std::cout << n << ":Args" << std::endl;
    args->onProgressCallback = [n](int current, int total) -> bool {
        std::cout << "\r" << n << ":Downloaded " << current << " bytes out of " << total << std::endl;; 
        return true;
    };
}