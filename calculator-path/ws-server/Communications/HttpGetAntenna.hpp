#pragma once
#include "HttpGetAbs.hpp"
#include "../common.h"
#include <vector>

class HttpGetAntenna : public HttpGetAbs{
    public:
    HttpGetAntenna(std::vector<std::vector<double>> vlatlon, int n) : vlatlon(vlatlon), n(n), heightsTx(), client(true){};
    virtual void request(HttpGet::OnReady onReady) override final;
    virtual const std::vector<float>& get() const override final;
    private:
    std::vector<std::vector<double>> vlatlon;  
    int n;
    std::vector<float> heightsTx;
    ix::HttpClient client;
};
