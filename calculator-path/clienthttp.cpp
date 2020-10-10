#include <ws-lib/ixwebsocket/IXHttpClient.h>
#include <iostream>

using namespace ix;

int main()
{
    HttpClient httpClient;
    HttpRequestArgsPtr args = httpClient.createRequest();

    // Custom headers can be set
    WebSocketHttpHeaders headers;
    headers["Foo"] = "bar";
    args->extraHeaders = headers;

    // Timeout options
    // args->connectTimeout = connectTimeout;
    // args->transferTimeout = transferTimeout;

    // // Redirect options
    // args->followRedirects = followRedirects;
    // args->maxRedirects = maxRedirects;

    // // Misc
    // args->compress = compress; // Enable gzip compression
    // args->verbose = verbose;
    args->logger = [](const std::string& msg)
    {
        std::cout << msg;
    };

    //
    // Synchronous Request
    //
    HttpResponsePtr out;
    std::string url = "https://www.google.com";

    // HEAD request
    out = httpClient.head(url, args);

    // GET request
    out = httpClient.get(url, args);

    // POST request with parameters
    HttpParameters httpParameters;
    httpParameters["foo"] = "bar";
    out = httpClient.post(url, httpParameters, args);

    // POST request with a body
    out = httpClient.post(url, std::string("foo=bar"), args);

    //
    // Result
    //
    HttpResponsePtr response;

    auto statusCode = response->statusCode; // Can be HttpErrorCode::Ok, HttpErrorCode::UrlMalformed, etc...
    auto errorCode = response->errorCode; // 200, 404, etc...
    auto responseHeaders = response->headers; // All the headers in a special case-insensitive unordered_map of (string, string)
    // auto body = response->body; // All the bytes from the response as an std::string
    auto errorMsg = response->errorMsg; // Descriptive error message in case of failure
    auto uploadSize = response->uploadSize; // Byte count of uploaded data
    auto downloadSize = response->downloadSize; // Byte count of downloaded data
    
    // std::cout < errorCode << "\n";

    return 0;
}