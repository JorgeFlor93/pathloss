#pragma once
#include "HttpGet.hpp"
#include <ixwebsocket/IXHttpClient.h>
#include <chrono>
#include <thread>

class HttpGetAbs : public HttpGet{
    protected:
    void configureArgs(ix::HttpRequestArgsPtr& args, int n);
};