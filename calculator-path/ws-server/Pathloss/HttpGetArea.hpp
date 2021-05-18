
#pragma once
#include "../common.h"
#include <string>
#include <vector> 
#include <ixwebsocket/IXHttpClient.h>
#include "../json.hpp"
#include <typeinfo>
#include <sstream>
#include "../Communications/Websocket.hpp"
#include "HttpGetAbs.hpp"

class HttpGetArea : public HttpGetAbs{
    public:
    HttpGetArea(path corners) : corners(corners), client(true), heights(){}; 
    ~HttpGetArea();
    virtual void request(HttpGet::OnReady onReady) override final;
    virtual const std::vector<float>& get() const override final;
    private:
    path corners;
    ix::HttpClient client;
    std::vector<float> heights;
    void decoder(HttpGet::OnReady onReady, const ix::HttpResponsePtr& response);
};

template < typename Type > std::string to_str (const Type & t)
{
  std::ostringstream os;
  os << t;
  return os.str ();
}