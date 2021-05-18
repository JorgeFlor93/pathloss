#pragma once
#include <ixwebsocket/IXHttp.h>
#include <functional>
#include <vector>

class HttpGet{
    public:
    // virtual ~HttpGet(){};
    using OnReady = std::function<void(void)>;
    virtual void request(HttpGet::OnReady onReady) = 0;
    virtual const std::vector<float>& get() const = 0;
};