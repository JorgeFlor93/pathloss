
#include "HttpGetAbs.hpp"
#include <iostream>

void HttpGetAbs::configureArgs(ix::HttpRequestArgsPtr& args){
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
    args->logger = [](const std::string& msg) { std::cout << msg << std::endl; };
    args->onProgressCallback = [](int current, int total) -> bool {
        std::cout << "\r" << "Downloaded " << current << " bytes out of " << total << std::endl;
        return true;
    };
}