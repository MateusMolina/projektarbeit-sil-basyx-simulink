#include <curl/curl.h>
#include <urlhandler/urlHandler.hpp>
#include "httpclient/curlHttpConnection.hpp"
#include <stdexcept>


// https://curl.se/libcurl/c/libcurl-tutorial.html

size_t CurlHttpConnection::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

CurlHttpConnection::CurlHttpConnection() {

}


HttpResponse CurlHttpConnection::get(const Url &url){
    this->initCurl();
    this->perform(url);
    return response;
}

HttpResponse CurlHttpConnection::post(const Url &url, string &&payload){
    this->initCurl();
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
    string buffer;
    string urlStr =  url.getStr();
    long httpCode;

    curl_easy_setopt(_curlHandle, CURLOPT_WRITEDATA, &buffer);
    curlCode = curl_easy_setopt(_curlHandle, CURLOPT_URL,  urlStr.c_str());

    curlCode = curl_easy_perform(_curlHandle);

    curl_easy_getinfo(_curlHandle, CURLINFO_RESPONSE_CODE, &httpCode);

    curl_easy_cleanup(_curlHandle);

    response.raw = buffer;
    response.httpCode = httpCode;
}

void CurlHttpConnection::initCurl(){
    _curlHandle = curl_easy_init(); 
    if(_curlHandle){
        curl_easy_setopt(_curlHandle, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(_curlHandle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        curl_easy_setopt(_curlHandle, CURLOPT_SSL_VERIFYPEER, 0L);          // TODO Remove CURLOPT_SSL_VERIFYPEER
        curl_easy_setopt(_curlHandle, CURLOPT_FOLLOWLOCATION, TRUE);
    }else
        throw std::runtime_error("Failed to stabilish connection to cURL");
}

CurlHttpConnection::~CurlHttpConnection(){
    // curl_easy_cleanup(_curlHandle);
}

