#ifndef _HTTPCONNECTION_
#define _HTTPCONNECTION_

#include<string>
#include <curl/curl.h>

using std::string;


class HttpConnection{
    private:

    public:
        CURLcode curlCode = CURLE_OK;
        CURL* _curlHandle;

        HttpConnection(const string &urlStr);
 
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

        static HttpConnection startHttpConnection(const string &urlStr);
        
        ~HttpConnection();

        void post(string &&payload);

        void put(string &&payload);

        string get();  
        
        CURLcode getCurlCode() { return curlCode; }
};

#endif
