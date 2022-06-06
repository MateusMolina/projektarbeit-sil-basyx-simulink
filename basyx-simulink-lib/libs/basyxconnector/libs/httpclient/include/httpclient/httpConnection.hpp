#ifndef _HTTPCONNECTION_
#define _HTTPCONNECTION_

#include<string>
#include <urlhandler/urlHandler.hpp>

using std::string;

struct HttpResponse{
    HttpResponse() : raw(""), httpCode(0) {}
    HttpResponse(string raw, long code) : raw(raw), httpCode(code) {};
    
    string raw = ""; 
    long httpCode = 0;
};
class HttpConnection{
    public:
        virtual ~HttpConnection() {};

        virtual HttpResponse post(const Url &url, const string &payload) = 0;

        virtual HttpResponse put(const Url &url, const string &payload) = 0;

        virtual HttpResponse get(const Url &url) = 0;  

        virtual HttpResponse getCurrentResponse() = 0;
};

#endif
