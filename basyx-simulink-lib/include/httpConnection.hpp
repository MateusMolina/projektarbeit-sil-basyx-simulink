#ifndef _HTTPCONNECTION_
#define _HTTPCONNECTION_

#include<string>
#include<curl/curl.h>
#include"urlHandler.hpp"

using std::string;

struct HttpResponse{
    string raw; 
    CURLcode curlCode;
};
class HttpConnection{
    private:
        CURLcode curlCode = CURLE_OK;
        CURL* _curlHandle;
        string readBuffer;

    public:


        HttpConnection(Url& url);       
 
        ~HttpConnection();

        HttpResponse post(string &&payload);

        HttpResponse put(string &&payload);

        HttpResponse get();  
        
        CURLcode getCurlCode() { return curlCode; }

        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
};

#endif
