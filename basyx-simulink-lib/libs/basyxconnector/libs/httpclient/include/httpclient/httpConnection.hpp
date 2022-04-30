#ifndef _HTTPCONNECTION_
#define _HTTPCONNECTION_

#include<string>
#include <urlhandler/urlHandler.hpp>

using std::string;

struct HttpResponse{
    HttpResponse() : raw(""), httpCode(0) {}
    HttpResponse(string raw, long code) : raw(raw), httpCode(httpCode) {};
    
    string raw; 
    long httpCode;
};
class HttpConnection{
    public:
        virtual ~HttpConnection() {};

        virtual HttpResponse post(const Url &url, string &&payload) = 0;

        virtual HttpResponse put(const Url &url, string &&payload) = 0;

        virtual HttpResponse get(const Url &url) = 0;  

};

#endif
