
#include<curl/curl.h>
#include"httpConnection.hpp"

class CurlHttpConnection : public HttpConnection{
    private:
        CURLcode curlCode = CURLE_OK;
        CURL* _curlHandle; //TODO change to smart ptr
        string readBuffer;
        HttpResponse response;

        void perform(const Url &url);

        void initCurl();
    public:
        CurlHttpConnection();
 
        ~CurlHttpConnection();

        HttpResponse post(const Url &url, const string &payload) override;

        HttpResponse put(const Url &url, const string &payload) override;

        HttpResponse get(const Url &url) override;  
        
        CURLcode getCurlCode() { return curlCode; }

        HttpResponse getCurrentResponse() override { return response; }

        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
};
