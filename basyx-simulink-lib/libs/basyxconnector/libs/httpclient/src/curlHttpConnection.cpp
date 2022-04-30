#include <curl/curl.h>
#include <urlhandler/urlHandler.hpp>
#include "httpclient/curlHttpConnection.hpp"


// https://curl.se/libcurl/c/libcurl-tutorial.html

size_t CurlHttpConnection::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

CurlHttpConnection::CurlHttpConnection() {
    _curlHandle = curl_easy_init(); 
    curl_easy_setopt(_curlHandle, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(_curlHandle, CURLOPT_WRITEDATA, &readBuffer);
}


HttpResponse CurlHttpConnection::get(const Url &url){
    this->perform(url);
    return response;
}

HttpResponse CurlHttpConnection::post(const Url &url, string &&payload){
    const char* data = payload.data();
    curl_easy_setopt(_curlHandle, CURLOPT_POSTFIELDS, data);

    this->perform(url);
    return response;
}

// TODO Implement
HttpResponse CurlHttpConnection::put(const Url &url, string &&payload){
    return HttpResponse();
}

void CurlHttpConnection::perform(const Url &url){
    string urlStr =  url.getStr();
    curl_easy_setopt(_curlHandle, CURLOPT_URL, urlStr.c_str());
    curl_easy_getinfo(_curlHandle, CURLINFO_RESPONSE_CODE, &response.httpCode);
    response.raw = readBuffer;
}

CurlHttpConnection::~CurlHttpConnection(){
    curl_easy_cleanup(_curlHandle);
}

