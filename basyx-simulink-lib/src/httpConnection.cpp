#include <curl/curl.h>
#include "../include/httpConnection.hpp"


// https://curl.se/libcurl/c/libcurl-tutorial.html

size_t HttpConnection::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


HttpConnection::HttpConnection(const string &urlStr){
    _curlHandle = curl_easy_init(); 
    curl_easy_setopt(_curlHandle, CURLOPT_URL, urlStr.c_str());

}

HttpConnection HttpConnection::startHttpConnection(const string &urlStr){
    return HttpConnection(urlStr);
}

string HttpConnection::get(){
    string readBuffer;
    curl_easy_setopt(_curlHandle, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(_curlHandle, CURLOPT_WRITEDATA, &readBuffer);
    curlCode = curl_easy_perform(_curlHandle);
    return readBuffer;
}

void HttpConnection::post(string &&payload){
    char* data = payload.data();
    curl_easy_setopt(_curlHandle, CURLOPT_POSTFIELDS, data);
    curlCode = curl_easy_perform(_curlHandle);
}

void HttpConnection::put(string &&payload){

}

HttpConnection::~HttpConnection(){
    curl_easy_cleanup(_curlHandle);
}

