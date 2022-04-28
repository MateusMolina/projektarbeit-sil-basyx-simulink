#include "../include/urlHandler.hpp"


Url::Url(const string &url){
    urlStr = url;
}

string Url::getStr(){
    return urlStr;
}

string Url::getRootUrlStr(){
    return rootUrlStr;
}

string Url::getApiPath(){
    return apiPath;
}

string Url::getEndPointPath(){
    return endpointPath;
}

void Url::setApiPath(const string &apiPath){
    Url::apiPath = apiPath;
}

void Url::setEndPointPath(const string &endpointPath){
    Url::endpointPath = endpointPath;
}