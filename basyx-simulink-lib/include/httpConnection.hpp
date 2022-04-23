#ifndef _HTTPCONNECTION_
#define _HTTPCONNECTION_

#include<string>
#include <curl/curl.h>

using std::string;

struct HttpResponse{
    string raw; 
    CURLcode curlCode;
};
class HttpConnection{
    private:
        CURLcode curlCode = CURLE_OK;
        CURL* _curlHandle;

    public:

        HttpConnection(const string &urlStr);
 
        ~HttpConnection();

        HttpResponse post(string &&payload);

        HttpResponse put(string &&payload);

        HttpResponse get();  
        
        CURLcode getCurlCode() { return curlCode; }

        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
};

#endif
